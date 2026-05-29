/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#define MAX_DELAY 96000
#define MAX_COMB 4800

//==============================================================================
/**
*/
class GainAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    GainAudioProcessor();
    ~GainAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    int getNumParameters() override;
    float getParameter(int index) override;
    void setParameter(int index, float newValue) override;
    const String getParameterName(int index) override;
    const String getParameterText(int index) override;
    enum Parameters { gain = 0, fr, delay, feedback,
        threshold, ratio , attack , release , makeup,
        overdrive, overdriveon, distort, distorttype,
        levell, levelr, peakl, peakr,
        chorusDelay, chorusMix,
        totalNumParam };
    bool NeedsUIUpdate() { return UIUpdateFlag; };
    void RequestUIUpdate() { UIUpdateFlag = true; };
    void ClearUIUpdateFlag() { UIUpdateFlag = false; };
    void updateFilterParameter(float freq);

private:
    float UserParams[totalNumParam];
    bool UIUpdateFlag;

    // var si fctpt filtru
    float a[3];
    float  b[3];
    float w[2][2]; //vector de stare z^-1 w[ch][n]
    float filterSample(int ch,float in);

    //var pt delay
    float dl[2][MAX_DELAY];
    int poz_in[2];

    //var pt compresor
    dsp::Compressor<float> compressor;
    //var pt vu meter
    float lastPeak[2];

    //var pt chorus
    float chBuf0[2][MAX_COMB];
    float chBuf1[2][MAX_COMB];
    int chPos0[2];
    int chPos1[2];
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainAudioProcessor)
};
