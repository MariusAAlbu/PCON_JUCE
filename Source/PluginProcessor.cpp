/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GainAudioProcessor::GainAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    UserParams[gain] = 1.0f; // implicit castigul este 1
    UserParams[fr] = 1.0f; // echivalent cu 20000
    w[0][0] = 0.f;
    w[0][1] = 0.f;
    w[1][0] = 0.f;
    w[1][1] = 0.f;
    for (int i = 0; i < 3; i++)
    {
        a[i] = 0.f;
        b[i] = 0.f;
    }

    UserParams[delay] = 32.f / 1000.f;
    UserParams[feedback] = 0.f; 
    memset(dl[0], 0, MAX_DELAY * sizeof(float));
    memset(dl[1], 0, MAX_DELAY * sizeof(float));
    poz_in[0] = 0;
    poz_in[1] = 0;

    //pt compresor
    UserParams[threshold] = 1.f;
    UserParams[ratio] = 0.f;
    UserParams[attack] = 0.f;
    UserParams[release] = 0.f;
    UserParams[makeup] = 0.f;

    //pt procesare neliniara
    UserParams[overdrive] = 0.f;
    UserParams[overdriveon] = 0.f;
    UserParams[distort] = 0.f;
    UserParams[distorttype] = 0.f;

    //pt nivel si peak
    UserParams[peakl] = 0.f;
    UserParams[peakr] = 0.f;
    UserParams[levell] = 0.f;
    UserParams[levelr] = 0.f;
    lastPeak[0] = 0.f;
    lastPeak[1] = 0.f;

    //pt chorus
    UserParams[chorusDelay] = 0.02f;
    UserParams[chorusMix] = 0.5f;
    for (int ch = 0; ch < 2; ch++)
    {
        memset(chBuf0[ch], 0, MAX_COMB * sizeof(float));
        memset(chBuf1[ch], 0, MAX_COMB * sizeof(float));
        chPos0[ch] = 0;
        chPos1[ch] = 0;
    }


    UIUpdateFlag = true;
}

GainAudioProcessor::~GainAudioProcessor()
{
}

//==============================================================================
const juce::String GainAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GainAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GainAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GainAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GainAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GainAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GainAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GainAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String GainAudioProcessor::getProgramName (int index)
{
    return {};
}

void GainAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void GainAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    const dsp::ProcessSpec spec = { sampleRate, (uint32)samplesPerBlock, (uint32)getTotalNumInputChannels() };

    //init compresor
    compressor.prepare(spec);
    compressor.reset();
    float max = powf(10, 0.f / 20.f);
    float min = powf(10, -100.f / 20.f);
    float val = UserParams[threshold] * (max - min) + min;
    float valdb = 20 * log10f(val);
    compressor.setThreshold(valdb);
    val = UserParams[ratio] * (10.f - 1.f) + 1.f;
    compressor.setRatio(val);
    val = UserParams[attack] * 200.f;
    compressor.setAttack(val);
    val = UserParams[release] * 1000.f;
    compressor.setRelease(val);
}

void GainAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GainAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void GainAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    float gainDenorm = UserParams[gain] * (1 - powf(10.f, -70.f / 20.f)) + powf(10.f, -70.f / 20.f);
    // pr Delay
    int M = round(UserParams[delay]*getSampleRate());
    float feedbackDenorm = UserParams[feedback] * (1 - powf(10.f, -100.f / 20.f)) + powf(10.f, -100.f / 20.f);
    float max = powf(10, 20.f / 20.f);
    float min = powf(10, 0.f / 20.f);
    float makeupgain = UserParams[makeup] * (max - min) + min;

    //chorus cu iir comb filter
    float baseDelay = UserParams[chorusDelay] * (50.f / 1000.f) + (1.f / 1000.f);
    int M0 = (int)(baseDelay * getSampleRate());
    int M1 = (int)(baseDelay * 1.02f * getSampleRate());// amplit intarziata cu ~2%
        M0 = jlimit(1, MAX_COMB - 1, M0);
        M1 = jlimit(1, MAX_COMB - 1, M1);
    float g = 0.5f;
    float mix = UserParams[chorusMix];

    //const de integrare attack/release
    float tat = 0.001f;
    float kat = 1.f - expf(-2.2f / (tat * getSampleRate()));
    float trt = 0.250f;
    float krt = 1.f - expf(-2.2f / (trt * getSampleRate()));
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        for (int j = 0; j < buffer.getNumSamples(); j++)
        {
            //filtrare
            channelData[j] = filterSample(channel, channelData[j]);
            ////delay FIR
            //int poz_out = poz_in[channel] - M;
            //if (poz_out < 0)
            //    poz_out = poz_out + MAX_DELAY;
            //poz_in[channel]++;
            //if (poz_in[channel] == MAX_DELAY)
            //    poz_in[channel] = 0;
            //dl[channel][poz_in[channel]] = channelData[j];
            //channelData[j] = channelData[j] + dl[channel][poz_out] * feedbackDenorm;
            channelData[j] = compressor.processSample(channel,channelData[j]);
            // makeupgain
            channelData[j] = channelData[j] * makeupgain;

            //knob overdrive va amplifica pana la 10dB
            float x = channelData[j] * powf(10.f, UserParams[overdrive] * 10.f / 20.f);
            if (abs(x) < 1.f / 3.f)
                channelData[j] = 2 * x;
            else if (abs(x) < 2.f / 3.f)
            {
                if (x >= 0)
                    channelData[j] = (3.f - (2.f - 3.f * x) * (2.f - 3.f * x)) / 3.f;
                else
                    channelData[j] = -(3.f - (2.f + 3.f * x) * (2.f + 3.f * x)) / 3.f;
            }
            else
                if (x > 0)
                    channelData[j] = 1;
                else
                    channelData[j] = -1;
            //distort
            if (UserParams[distorttype] == 1.f)
            {
                //dist sintetic
                float x = channelData[j] * powf(10.f, UserParams[distort] * 10.f / 20.f);
                if (x >= 0)
                    channelData[j] = 1.f - expf(-x);
                else
                    channelData[j] = expf(x) - 1.f;
            }
            else if ((UserParams[distorttype] == 0.5) && (UserParams[distort] != 0.f))
            {
                float Q = -0.05f;
                float dist = UserParams[distort] * 100.f;
                if (channelData[j] == Q)
                    channelData[j] = 1 / dist + Q / (1.f - expf(dist * Q));
                else
                    channelData[j] = (channelData[j] - Q) / (1.f - expf(-dist * channelData[j])) -
                    Q / (1.f - expf(dist * Q));
            }

            //chorus cu filtru IIR comb
            float dry = channelData[j];
            // Comb 0
            int readPos0 = chPos0[channel] - M0;
            if (readPos0 < 0) 
                readPos0 += MAX_COMB;
            float ch0out = dry + g * chBuf0[channel][readPos0];
            chBuf0[channel][chPos0[channel]] = ch0out;
            chPos0[channel] = (chPos0[channel] + 1) % MAX_COMB;

            // Comb 1
            int readPos1 = chPos1[channel] - M1;
            if (readPos1 < 0) readPos1 += MAX_COMB;
            float ch1out = dry + g * chBuf1[channel][readPos1];
            chBuf1[channel][chPos1[channel]] = ch1out;
            chPos1[channel] = (chPos1[channel] + 1) % MAX_COMB;
            //mix dry/wet
            float wet = (ch0out + ch1out) * 0.5f;
            channelData[j] = dry * (1.f - mix) + wet * mix;

            //delay IIR
            int poz_out = poz_in[channel] - M;
            if (poz_out < 0)
                poz_out = poz_out + MAX_DELAY;
            channelData[j] = channelData[j] + dl[channel][poz_out] * feedbackDenorm;
            poz_in[channel]++;
            if (poz_in[channel] == MAX_DELAY)
                poz_in[channel] = 0;
            dl[channel][poz_in[channel]] = channelData[j];
      
            // gain final
            channelData[j] = channelData[j] * gainDenorm;

            //calcul nivel peak
            if (channelData[j] < lastPeak[channel])
                lastPeak[channel] = (1.f - krt) * lastPeak[channel];
            else
                lastPeak[channel] = (1.f - krt - kat) * lastPeak[channel]+
                kat*abs(channelData[j]);
            if (channel == 0)
                UserParams[peakl] = lastPeak[0];
            else
                UserParams[peakr] = lastPeak[1];
        }
        // ..do something to the data...
    }
}

//==============================================================================
bool GainAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* GainAudioProcessor::createEditor()
{
    return new GainAudioProcessorEditor (this);
}

//==============================================================================
void GainAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    XmlElement root("Root");
    XmlElement* el;
    el = root.createNewChildElement("Gain");
    el->addTextElement(String(UserParams[gain]));

    el = root.createNewChildElement("Fr");
    el->addTextElement(String(UserParams[fr]));

    el = root.createNewChildElement("Delay");
    el->addTextElement(String(UserParams[delay]));

    el = root.createNewChildElement("Feedback");
    el->addTextElement(String(UserParams[feedback]));

    el = root.createNewChildElement("Threshold");
    el->addTextElement(String(UserParams[threshold]));

    el = root.createNewChildElement("Ratio");
    el->addTextElement(String(UserParams[ratio]));

    el = root.createNewChildElement("Attack");
    el->addTextElement(String(UserParams[attack]));

    el = root.createNewChildElement("Release");
    el->addTextElement(String(UserParams[release]));

    el = root.createNewChildElement("Makeup");
    el->addTextElement(String(UserParams[makeup]));

    el = root.createNewChildElement("Overdrive");
    el->addTextElement(String(UserParams[overdrive]));

    el = root.createNewChildElement("Distort");
    el->addTextElement(String(UserParams[distort]));

    el = root.createNewChildElement("Overdriveon");
    el->addTextElement(String(UserParams[overdriveon]));

    el = root.createNewChildElement("DistortType");
    el->addTextElement(String(UserParams[distorttype]));

    el = root.createNewChildElement("ChorusDelay");
    el->addTextElement(String(UserParams[chorusDelay]));

    el = root.createNewChildElement("ChorusMix");
    el->addTextElement(String(UserParams[chorusMix]));

    copyXmlToBinary(root, destData);
}

void GainAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    static std::unique_ptr< XmlElement > pRoot = getXmlFromBinary(data, sizeInBytes);
    if (pRoot != NULL)
    {
        forEachXmlChildElement((*pRoot), pChild)
        {
            if (pChild->hasTagName("Gain"))
            {
                String text = pChild->getAllSubText();
                setParameter(gain, text.getFloatValue());
            }
            if (pChild->hasTagName("Fr"))
            {
                String text = pChild->getAllSubText();
                setParameter(fr, text.getFloatValue());
            }
            if (pChild->hasTagName("Delay"))
            {
                String text = pChild->getAllSubText();
                setParameter(delay, text.getFloatValue());
            }
            if (pChild->hasTagName("Feedback"))
            {
                String text = pChild->getAllSubText();
                setParameter(feedback, text.getFloatValue());
            }
            if (pChild->hasTagName("Threshold"))
            {
                String text = pChild->getAllSubText();
                setParameter(threshold, text.getFloatValue());
            }
            if (pChild->hasTagName("Ratio"))
            {
                String text = pChild->getAllSubText();
                setParameter(ratio, text.getFloatValue());
            }
            if (pChild->hasTagName("Attack"))
            {
                String text = pChild->getAllSubText();
                setParameter(attack, text.getFloatValue());
            }
            if (pChild->hasTagName("Release"))
            {
                String text = pChild->getAllSubText();
                setParameter(release, text.getFloatValue());
            }
            if (pChild->hasTagName("Makeup"))
            {
                String text = pChild->getAllSubText();
                setParameter(makeup, text.getFloatValue());
            }
            if (pChild->hasTagName("Overdrive"))
            {
                String text = pChild->getAllSubText();
                setParameter(overdrive, text.getFloatValue());
            }
            if (pChild->hasTagName("Distort"))
            {
                String text = pChild->getAllSubText();
                setParameter(distort, text.getFloatValue());
            }
            if (pChild->hasTagName("Overdriveon"))
            {
                String text = pChild->getAllSubText();
                setParameter(overdriveon, text.getFloatValue());
            }
            if (pChild->hasTagName("DistortType"))
            {
                String text = pChild->getAllSubText();
                setParameter(distorttype, text.getFloatValue());
            }
            if (pChild->hasTagName("ChorusDelay"))
            {
                String text = pChild->getAllSubText();
                setParameter(chorusDelay, text.getFloatValue());
            }
            if (pChild->hasTagName("ChorusMix"))
            {
                String text = pChild->getAllSubText();
                setParameter(chorusMix, text.getFloatValue());
            }

        }
        UIUpdateFlag = true; // cere update de la GUI
    }
}

int GainAudioProcessor::getNumParameters()
{
    return totalNumParam;
}

float GainAudioProcessor::getParameter(int index)
{
    if ((index >= totalNumParam) || (index < 0))
        return 0.0f;
    else return UserParams[index];
    //switch (index)
    //{
    //case gain: // exemplu
    //    return UserParams[gain];
    //default: return 0.0f; // index invalid
    //}
}

void GainAudioProcessor::setParameter(int index, float newValue)
{
    float max, min, val;
    switch (index)
    {
    case gain:
        UserParams[gain] = newValue;
        break;
    case fr:
        UserParams[fr] = newValue;
        updateFilterParameter(newValue*(20000.f-20.f)+20.f);
        break;
    case delay:
        UserParams[delay] = newValue;
        break;
    case feedback:
        UserParams[feedback] = newValue;
        break;
    case threshold:
        UserParams[threshold] = newValue;
         max = powf(10, 0.f / 20.f);
         min = powf(10, -100.f / 20.f);
         val = newValue * (max - min) + min;
        compressor.setThreshold(20 * log10f(val));
        break;
    case ratio:
        UserParams[ratio] = newValue;
        compressor.setRatio(newValue * (10.f - 1.f) + 1.f);
        break;
    case attack:
        UserParams[attack] = newValue;
        compressor.setAttack(newValue * 200.f);
        break;
    case release:
        UserParams[release] = newValue;
        compressor.setRelease(newValue * 1000.f);
        break;
    case makeup:
        UserParams[makeup] = newValue;
        break;
    case overdrive:
        UserParams[overdrive] = newValue;
        break;
    case distort:
        UserParams[distort] = newValue;
        break;
    case overdriveon:
        UserParams[overdriveon] = newValue;
        break;
    case distorttype:
        UserParams[distorttype] = newValue;
        break;
    case chorusDelay:
        UserParams[chorusDelay] = newValue;
        break;
    case chorusMix:
        UserParams[chorusMix] = newValue;
        break;
    default: return;
    }

    UIUpdateFlag = true;
}

const String GainAudioProcessor::getParameterName(int index)
{
    switch (index)
    {
    case gain: return "Gain";
        break;
    case fr: return "Frequency";
        break;
    case delay: return "Delay";
        break;
    case feedback: return "Feedback";
        break;
    case threshold: return "Threshhold";
        break;
    case ratio: return "Ratio";
        break;
    case attack: return "Attack";
        break;
    case release: return "Release";
        break;
    case makeup: return "Makeup";
        break;
    case overdrive: return "Overdrive";
        break;
    case distort: return "Distort";
        break;
    case overdriveon: return "Overdriveon";
        break;
    case distorttype: return "DistortType";
        break;
    case chorusDelay: return "ChorusDelay";
        break;
    case chorusMix: return "ChorusMix";
        break;
      
    default:return String();
    }
}

const String GainAudioProcessor::getParameterText(int index)
{
    if (index >= 0 && index < totalNumParam)
        return String(UserParams[index]);
    else return String();
}

void GainAudioProcessor ::updateFilterParameter(float freq)
{
    float K = tanf(juce::float_Pi * freq / getSampleRate());
    float Q = 1 / sqrtf(2);
    float num = K * K * Q + K + Q;
    b[0] = K * K * Q / num;
    b[1] = 2 * b[0];
    b[2] = b[0];
    a[0] = 1;
    a[1] = 2 * Q * (K * K - 1) / num;
    a[2] = (K * K * Q - K + Q) / num;

}

float GainAudioProcessor::filterSample(int ch,float in)
{
    float aux = in - a[1] * w[ch][0] - a[2] * w[ch][1];
    float out = aux * b[0] + w[ch][0] * b[1] + w[ch][1] * b[2];
    w[ch][1] = w[ch][0];
    w[ch][0] = aux;
    return out;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GainAudioProcessor();
}
