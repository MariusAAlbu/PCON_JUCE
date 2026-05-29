/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 7.0.12

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
GainAudioProcessorEditor::GainAudioProcessorEditor (GainAudioProcessor* ownerFilter)
    : AudioProcessorEditor(ownerFilter)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    nonlineargroup.reset (new juce::GroupComponent ("Nonlinear Group",
                                                    TRANS ("Nonlinear processing")));
    addAndMakeVisible (nonlineargroup.get());

    nonlineargroup->setBounds (784, 24, 184, 207);

    peakLabel.reset (new juce::Label ("Peak Label",
                                      TRANS ("Peak")));
    addAndMakeVisible (peakLabel.get());
    peakLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    peakLabel->setJustificationType (juce::Justification::centredLeft);
    peakLabel->setEditable (false, false, false);
    peakLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    peakLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    peakLabel->setBounds (984, 192, 78, 24);

    compressorGroupBox.reset (new juce::GroupComponent ("Compressor Group Box",
                                                        TRANS ("Compressor")));
    addAndMakeVisible (compressorGroupBox.get());

    compressorGroupBox->setBounds (264, 88, 488, 143);

    delayKnob.reset (new juce::Slider ("delay Knob"));
    addAndMakeVisible (delayKnob.get());
    delayKnob->setRange (0, 1000, 1);
    delayKnob->setSliderStyle (juce::Slider::Rotary);
    delayKnob->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 40, 20);
    delayKnob->addListener (this);

    delayKnob->setBounds (16, 120, 110, 88);

    gainSlider.reset (new juce::Slider ("Gain Slider "));
    addAndMakeVisible (gainSlider.get());
    gainSlider->setTooltip (TRANS ("Regleaza nivelul"));
    gainSlider->setRange (-70, 0, 0.1);
    gainSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    gainSlider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    gainSlider->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff30393e));
    gainSlider->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0xff05354a));
    gainSlider->addListener (this);

    gainSlider->setBounds (64, 12, 271, 16);

    gainLabel.reset (new juce::Label ("Gain Label",
                                      TRANS ("Nivel dB\n")));
    addAndMakeVisible (gainLabel.get());
    gainLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
    gainLabel->setJustificationType (juce::Justification::centredRight);
    gainLabel->setEditable (false, false, false);
    gainLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    gainLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    gainLabel->setBounds (24, 8, 70, 24);

    frSlider.reset (new juce::Slider ("Freq Slider"));
    addAndMakeVisible (frSlider.get());
    frSlider->setRange (20, 20000, 1);
    frSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    frSlider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 40, 20);
    frSlider->addListener (this);

    frSlider->setBounds (120, 32, 150, 24);

    frLabel.reset (new juce::Label ("Freq Label",
                                    TRANS ("Frecventa(Hz)")));
    addAndMakeVisible (frLabel.get());
    frLabel->setFont (juce::Font (18.50f, juce::Font::plain).withTypefaceStyle ("Regular"));
    frLabel->setJustificationType (juce::Justification::centredLeft);
    frLabel->setEditable (false, false, false);
    frLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    frLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    frLabel->setBounds (8, 32, 150, 24);

    delayLabel.reset (new juce::Label ("Delay Label",
                                       TRANS ("Delay (ms)")));
    addAndMakeVisible (delayLabel.get());
    delayLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    delayLabel->setJustificationType (juce::Justification::centredLeft);
    delayLabel->setEditable (false, false, false);
    delayLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    delayLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    delayLabel->setBounds (32, 104, 150, 24);

    feedbackLabel.reset (new juce::Label ("Feedback Label",
                                          TRANS ("Feedback(dB)")));
    addAndMakeVisible (feedbackLabel.get());
    feedbackLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    feedbackLabel->setJustificationType (juce::Justification::centredLeft);
    feedbackLabel->setEditable (false, false, false);
    feedbackLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    feedbackLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    feedbackLabel->setBounds (128, 104, 150, 24);

    thresholdLabel.reset (new juce::Label ("Threshold Label",
                                           TRANS ("Threshold [dB]")));
    addAndMakeVisible (thresholdLabel.get());
    thresholdLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    thresholdLabel->setJustificationType (juce::Justification::centred);
    thresholdLabel->setEditable (false, false, false);
    thresholdLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    thresholdLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    thresholdLabel->setBounds (240, 104, 150, 24);

    thresholdKnob.reset (new juce::Slider ("Threshold Knob"));
    addAndMakeVisible (thresholdKnob.get());
    thresholdKnob->setRange (-100, 0, 0.1);
    thresholdKnob->setSliderStyle (juce::Slider::Rotary);
    thresholdKnob->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 40, 20);
    thresholdKnob->addListener (this);

    thresholdKnob->setBounds (240, 120, 134, 88);

    ratioKnob.reset (new juce::Slider ("Ratio Knob"));
    addAndMakeVisible (ratioKnob.get());
    ratioKnob->setRange (1, 20, 0.1);
    ratioKnob->setSliderStyle (juce::Slider::Rotary);
    ratioKnob->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 40, 20);
    ratioKnob->addListener (this);

    ratioKnob->setBounds (340, 120, 110, 88);

    ratioLabel2.reset (new juce::Label ("Ratio Label",
                                        TRANS ("Ratio")));
    addAndMakeVisible (ratioLabel2.get());
    ratioLabel2->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    ratioLabel2->setJustificationType (juce::Justification::centred);
    ratioLabel2->setEditable (false, false, false);
    ratioLabel2->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    ratioLabel2->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    ratioLabel2->setBounds (320, 104, 150, 24);

    attackKnob.reset (new juce::Slider ("Attack Knob"));
    addAndMakeVisible (attackKnob.get());
    attackKnob->setRange (0, 200, 0.1);
    attackKnob->setSliderStyle (juce::Slider::Rotary);
    attackKnob->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 50, 20);
    attackKnob->addListener (this);

    attackKnob->setBounds (440, 120, 110, 88);

    attackLabel.reset (new juce::Label ("Attack Label",
                                        TRANS ("Attack [ms]")));
    addAndMakeVisible (attackLabel.get());
    attackLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    attackLabel->setJustificationType (juce::Justification::centred);
    attackLabel->setEditable (false, false, false);
    attackLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    attackLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    attackLabel->setBounds (416, 104, 150, 24);

    releaseKnob.reset (new juce::Slider ("Release Knob"));
    addAndMakeVisible (releaseKnob.get());
    releaseKnob->setRange (0, 1000, 0.1);
    releaseKnob->setSliderStyle (juce::Slider::Rotary);
    releaseKnob->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 50, 20);
    releaseKnob->addListener (this);

    releaseKnob->setBounds (540, 120, 110, 88);

    releaseLabel.reset (new juce::Label ("Release Label",
                                         TRANS ("Release [ms]")));
    addAndMakeVisible (releaseLabel.get());
    releaseLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    releaseLabel->setJustificationType (juce::Justification::centred);
    releaseLabel->setEditable (false, false, false);
    releaseLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    releaseLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    releaseLabel->setBounds (520, 104, 150, 24);

    makeupKnob.reset (new juce::Slider ("Makeup Knob"));
    addAndMakeVisible (makeupKnob.get());
    makeupKnob->setRange (0, 40, 0.1);
    makeupKnob->setSliderStyle (juce::Slider::Rotary);
    makeupKnob->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 40, 20);
    makeupKnob->addListener (this);

    makeupKnob->setBounds (640, 120, 115, 88);

    makeupLabel.reset (new juce::Label ("Makeup Label",
                                        TRANS ("Makeup [dB]")));
    addAndMakeVisible (makeupLabel.get());
    makeupLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    makeupLabel->setJustificationType (juce::Justification::centred);
    makeupLabel->setEditable (false, false, false);
    makeupLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    makeupLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    makeupLabel->setBounds (624, 104, 150, 24);

    feedbackKnob3.reset (new juce::Slider ("Feedback Knob"));
    addAndMakeVisible (feedbackKnob3.get());
    feedbackKnob3->setRange (-100, 0, 1);
    feedbackKnob3->setSliderStyle (juce::Slider::Rotary);
    feedbackKnob3->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 40, 20);
    feedbackKnob3->addListener (this);

    feedbackKnob3->setBounds (112, 120, 126, 88);

    delayGroupBox.reset (new juce::GroupComponent ("new group",
                                                   TRANS ("Delay Effect")));
    addAndMakeVisible (delayGroupBox.get());

    delayGroupBox->setBounds (0, 88, 256, 142);

    overdriveKnob.reset (new juce::Slider ("Overdrive Knob"));
    addAndMakeVisible (overdriveKnob.get());
    overdriveKnob->setRange (0, 100, 1);
    overdriveKnob->setSliderStyle (juce::Slider::Rotary);
    overdriveKnob->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 40, 20);
    overdriveKnob->addListener (this);

    overdriveKnob->setBounds (776, 64, 115, 88);

    overdriveLabel.reset (new juce::Label ("Overdrive Label",
                                           TRANS ("Overdrive")));
    addAndMakeVisible (overdriveLabel.get());
    overdriveLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    overdriveLabel->setJustificationType (juce::Justification::centred);
    overdriveLabel->setEditable (false, false, false);
    overdriveLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    overdriveLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    overdriveLabel->setBounds (760, 40, 150, 24);

    distortKnob.reset (new juce::Slider ("Distort Knob"));
    addAndMakeVisible (distortKnob.get());
    distortKnob->setRange (0, 100, 1);
    distortKnob->setSliderStyle (juce::Slider::Rotary);
    distortKnob->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 40, 20);
    distortKnob->addListener (this);

    distortKnob->setBounds (864, 64, 115, 88);

    distortLabel.reset (new juce::Label ("Distort Label",
                                         TRANS ("Distortion")));
    addAndMakeVisible (distortLabel.get());
    distortLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    distortLabel->setJustificationType (juce::Justification::centred);
    distortLabel->setEditable (false, false, false);
    distortLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    distortLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    distortLabel->setBounds (848, 40, 150, 24);

    overdriveToggle.reset (new juce::ToggleButton ("Overdrive Toggle"));
    addAndMakeVisible (overdriveToggle.get());
    overdriveToggle->setButtonText (TRANS ("Active"));
    overdriveToggle->addListener (this);

    overdriveToggle->setBounds (800, 192, 70, 24);

    distortCombo.reset (new juce::ComboBox ("Distort Combo"));
    addAndMakeVisible (distortCombo.get());
    distortCombo->setEditableText (false);
    distortCombo->setJustificationType (juce::Justification::centredLeft);
    distortCombo->setTextWhenNothingSelected (juce::String());
    distortCombo->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    distortCombo->addItem (TRANS ("Off"), 1);
    distortCombo->addItem (TRANS ("Valve"), 2);
    distortCombo->addItem (TRANS ("Synthetic"), 3);
    distortCombo->addListener (this);

    distortCombo->setBounds (832, 160, 126, 24);

    delayChKnob.reset (new juce::Slider ("Delay Ch Knob"));
    addAndMakeVisible (delayChKnob.get());
    delayChKnob->setRange (0, 50, 1);
    delayChKnob->setSliderStyle (juce::Slider::Rotary);
    delayChKnob->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 40, 20);
    delayChKnob->addListener (this);

    delayChKnob->setBounds (1078, 120, 115, 88);

    delayChLabel.reset (new juce::Label ("Delay Ch Label",
                                         TRANS ("Delay")));
    addAndMakeVisible (delayChLabel.get());
    delayChLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    delayChLabel->setJustificationType (juce::Justification::centred);
    delayChLabel->setEditable (false, false, false);
    delayChLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    delayChLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    delayChLabel->setBounds (1061, 104, 150, 24);

    drywetKnob.reset (new juce::Slider ("Dry Wet Knob"));
    addAndMakeVisible (drywetKnob.get());
    drywetKnob->setRange (0, 100, 1);
    drywetKnob->setSliderStyle (juce::Slider::Rotary);
    drywetKnob->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 40, 20);
    drywetKnob->addListener (this);

    drywetKnob->setBounds (1184, 118, 115, 88);

    drywetLabel.reset (new juce::Label ("Dry Wet Label",
                                        TRANS ("Dry/Wet")));
    addAndMakeVisible (drywetLabel.get());
    drywetLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    drywetLabel->setJustificationType (juce::Justification::centred);
    drywetLabel->setEditable (false, false, false);
    drywetLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    drywetLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    drywetLabel->setBounds (1167, 102, 150, 24);

    juce__groupComponent2.reset (new juce::GroupComponent ("new group",
                                                           TRANS ("group")));
    addAndMakeVisible (juce__groupComponent2.get());

    juce__groupComponent2->setBounds (1096, 88, 200, 150);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (1600, 250);


    //[Constructor] You can add your own custom stuff here..
    getProcessor()->RequestUIUpdate();
    startTimer(20);
    frSlider->setSkewFactorFromMidPoint(1000.f);
    counter = 0;
    //[/Constructor]
}

GainAudioProcessorEditor::~GainAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    nonlineargroup = nullptr;
    peakLabel = nullptr;
    compressorGroupBox = nullptr;
    delayKnob = nullptr;
    gainSlider = nullptr;
    gainLabel = nullptr;
    frSlider = nullptr;
    frLabel = nullptr;
    delayLabel = nullptr;
    feedbackLabel = nullptr;
    thresholdLabel = nullptr;
    thresholdKnob = nullptr;
    ratioKnob = nullptr;
    ratioLabel2 = nullptr;
    attackKnob = nullptr;
    attackLabel = nullptr;
    releaseKnob = nullptr;
    releaseLabel = nullptr;
    makeupKnob = nullptr;
    makeupLabel = nullptr;
    feedbackKnob3 = nullptr;
    delayGroupBox = nullptr;
    overdriveKnob = nullptr;
    overdriveLabel = nullptr;
    distortKnob = nullptr;
    distortLabel = nullptr;
    overdriveToggle = nullptr;
    distortCombo = nullptr;
    delayChKnob = nullptr;
    delayChLabel = nullptr;
    drywetKnob = nullptr;
    drywetLabel = nullptr;
    juce__groupComponent2 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void GainAudioProcessorEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff24882f));

    //[UserPaint] Add your own custom painting code here..
    int x, y, w, h;
    float pxdb = 160.f / 60.f;
    // desenam dreptunghiurile colorate
    g.setColour(Colour(0xffea8413));//portocaliu
    x = 1000;
    y = 32;
    w = 45;
    h = round(6.f * pxdb);
    g.fillRect(x, y, w, h);
    x = 1049;
    g.fillRect(x, y, w, h);

    g.setColour(Colour(0xffebd30d));//galben
    x = 1000;
    y = y + h;
    g.fillRect(x, y, w, h);
    x = 1049;
    g.fillRect(x, y, w, h);
    g.setColour(Colour(0xff012d34));//albastru inchis
    x = 1000;
    y = y + h;
    h = round(48.f * pxdb);
    g.fillRect(x, y, w, h);
    x = 1049;
    g.fillRect(x, y, w, h);

    //g.setColour(Colour(0xff000000));//negru
    //x = 1000;
    //y = 32;
    //h = round(-levelLdb * pxdb);
    //g.fillRect(x, y, w, h);
    //x = 1049;
    //h = round(-levelRdb * pxdb);
    //g.fillRect(x, y, w, h);
    //[/UserPaint]
}

void GainAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void GainAudioProcessorEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    GainAudioProcessor* ourProcessor = getProcessor();
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == delayKnob.get())
    {
        //[UserSliderCode_delayKnob] -- add your slider handling code here..
        float delayNorm = (float)delayKnob->getValue() / 1000.f;
        ourProcessor->setParameter(GainAudioProcessor::delay, delayNorm);
        //[/UserSliderCode_delayKnob]
    }
    else if (sliderThatWasMoved == gainSlider.get())
    {
        //[UserSliderCode_gainSlider] -- add your slider handling code here..
        float gainDenorm = powf(10.f, (float)gainSlider->getValue() / 20.f);
        float gainNorm =  (gainDenorm - powf(10.f,-70.f/20.f)) / (1.f - powf(10.f, -70.f / 20.f));
        ourProcessor->setParameter(GainAudioProcessor::gain, gainNorm);
        //[/UserSliderCode_gainSlider]
    }
    else if (sliderThatWasMoved == frSlider.get())
    {
        //[UserSliderCode_frSlider] -- add your slider handling code here..
        float frNorm = ((float)frSlider->getValue() - 20.f) / (20000.f - 20.f);
        ourProcessor->setParameter(GainAudioProcessor::fr, frNorm);
        //[/UserSliderCode_frSlider]
    }
    else if (sliderThatWasMoved == thresholdKnob.get())
    {
        //[UserSliderCode_thresholdKnob] -- add your slider handling code here..
        float val = powf(10, thresholdKnob->getValue() / 20.f);
        float max = powf(10, 0.f / 20.f);
        float min = powf(10, -100.f / 20.f);
        float valNorm = (val - min) / (max - min);
        ourProcessor->setParameter(GainAudioProcessor::threshold, valNorm);
        //[/UserSliderCode_thresholdKnob]
    }
    else if (sliderThatWasMoved == ratioKnob.get())
    {
        //[UserSliderCode_ratioKnob] -- add your slider handling code here..
        float valNorm = (ratioKnob->getValue() - 1.f) / (10.f - 1.f);
        ourProcessor->setParameter(GainAudioProcessor::ratio, valNorm);
        //[/UserSliderCode_ratioKnob]
    }
    else if (sliderThatWasMoved == attackKnob.get())
    {
        //[UserSliderCode_attackKnob] -- add your slider handling code here..
        float valNorm = attackKnob->getValue() / 200.f;
        ourProcessor->setParameter(GainAudioProcessor::attack, valNorm);
        //[/UserSliderCode_attackKnob]
    }
    else if (sliderThatWasMoved == releaseKnob.get())
    {
        //[UserSliderCode_releaseKnob] -- add your slider handling code here..
        float valNorm = releaseKnob->getValue() / 1000.f;
        ourProcessor->setParameter(GainAudioProcessor::release, valNorm);
        //[/UserSliderCode_releaseKnob]
    }
    else if (sliderThatWasMoved == makeupKnob.get())
    {
        //[UserSliderCode_makeupKnob] -- add your slider handling code here..
        float val = powf(10, makeupKnob->getValue() / 20.f);
        float max = powf(10, 20.f / 20.f);
        float min = powf(10, 0.f / 20.f);
        float valNorm = (val - min) / (max - min);
        ourProcessor->setParameter(GainAudioProcessor::makeup, valNorm);
        //[/UserSliderCode_makeupKnob]
    }
    else if (sliderThatWasMoved == feedbackKnob3.get())
    {
        //[UserSliderCode_feedbackKnob3] -- add your slider handling code here..
        float feedbackDenorm = powf(10.f, (float)feedbackKnob3->getValue() / 20.f);
        float feedbackNorm = (feedbackDenorm - powf(10.f, -100.f / 20.f)) / (1.f - powf(10.f, -100.f / 20.f));
        ourProcessor->setParameter(GainAudioProcessor::feedback, feedbackNorm);
        //[/UserSliderCode_feedbackKnob3]
    }
    else if (sliderThatWasMoved == overdriveKnob.get())
    {
        //[UserSliderCode_overdriveKnob] -- add your slider handling code here..
        float valNorm = overdriveKnob->getValue() / 100.f;
        ourProcessor->setParameter(GainAudioProcessor::overdrive, valNorm);
        //[/UserSliderCode_overdriveKnob]
    }
    else if (sliderThatWasMoved == distortKnob.get())
    {
        //[UserSliderCode_distortKnob] -- add your slider handling code here..
        float valNorm = distortKnob->getValue() / 100.f;
        ourProcessor->setParameter(GainAudioProcessor::distort, valNorm);
        //[/UserSliderCode_distortKnob]
    }
    else if (sliderThatWasMoved == delayChKnob.get())
    {
        //[UserSliderCode_delayChKnob] -- add your slider handling code here..
        float valNorm = ((float)delayChKnob->getValue() - 1.f) / 50.f;
        ourProcessor->setParameter(GainAudioProcessor::chorusDelay, valNorm);
        //[/UserSliderCode_delayChKnob]
    }
    else if (sliderThatWasMoved == drywetKnob.get())
    {
        //[UserSliderCode_drywetKnob] -- add your slider handling code here..
        float valNorm = (float)drywetKnob->getValue() / 100.f;
        ourProcessor->setParameter(GainAudioProcessor::chorusMix, valNorm);
        //[/UserSliderCode_drywetKnob]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void GainAudioProcessorEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    GainAudioProcessor* ourProcessor = getProcessor();
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == overdriveToggle.get())
    {
        //[UserButtonCode_overdriveToggle] -- add your button handler code here..
        float val = 0.f;
        if (overdriveToggle->getToggleState())
            val = 1.f;
        //[UsersliderValueChanged_Pre]
        ourProcessor->setParameter(GainAudioProcessor::overdriveon, val);
        //[/UserButtonCode_overdriveToggle]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void GainAudioProcessorEditor::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    GainAudioProcessor* ourProcessor = getProcessor();
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == distortCombo.get())
    {
        //[UserComboBoxCode_distortCombo] -- add your combo box handling code here..
        float val = (float)distortCombo->getSelectedItemIndex() / 2.f;
        if(val>=0)
            ourProcessor->setParameter(GainAudioProcessor::distorttype, val);
        //[/UserComboBoxCode_distortCombo]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void GainAudioProcessorEditor::timerCallback()
{
    GainAudioProcessor* ourProcessor = getProcessor();
    if (ourProcessor->NeedsUIUpdate())
    {
        float gainNorm = ourProcessor->getParameter(GainAudioProcessor::gain);
        float gainDenorm = gainNorm * (1 - powf(10.f, -70.f / 20.f)) + powf(10.f, -70.f / 20.f);
        float dbValue = 20.f * log10f(gainDenorm);
        gainSlider->setValue(dbValue, juce::dontSendNotification);

        float frNorm = ourProcessor->getParameter(GainAudioProcessor::fr);
        float fr = frNorm * (20000.f - 20.f) + 20.f;
        frSlider->setValue(fr, dontSendNotification);

        float delayNorm = ourProcessor->getParameter(GainAudioProcessor::delay);
        float delay = delayNorm * 1000.f;
        delayKnob->setValue(delay, dontSendNotification);

        float feedbackNorm = ourProcessor->getParameter(GainAudioProcessor::feedback);
        float feedbackDenorm = feedbackNorm * (1 - powf(10.f, -100.f / 20.f)) + powf(10.f, -100.f / 20.f);
        float feedbackdb = 20.f * log10f(feedbackDenorm);
        feedbackKnob3->setValue(feedbackdb, juce::dontSendNotification);

        float thresholdNorm = ourProcessor->getParameter(GainAudioProcessor::threshold);
        float max = powf(10, 0.f / 20.f);
        float min = powf(10, -100.f / 20.f);
        float val = thresholdNorm * (max - min) + min;
        float valdb = 20 * log10f(val);
        thresholdKnob->setValue(valdb, dontSendNotification);

        float ratioNorm = ourProcessor->getParameter(GainAudioProcessor::ratio);
        float ratio = ratioNorm * (10.f - 1.f) + 1.f;
        ratioKnob->setValue(ratio, dontSendNotification);

        float attackNorm = ourProcessor->getParameter(GainAudioProcessor::attack);
        float attack = attackNorm * 200.f;
        attackKnob->setValue(attack, dontSendNotification);

        float releaseNorm = ourProcessor->getParameter(GainAudioProcessor::release);
        float release = releaseNorm * 1000.f;
        releaseKnob->setValue(release, dontSendNotification);

        float makeupNorm = ourProcessor->getParameter(GainAudioProcessor::makeup);
         max = powf(10, 20.f / 20.f);
         min = powf(10, 0.f / 20.f);
         val = makeupNorm * (max - min) + min;
         valdb = 20 * log10f(val);
        makeupKnob->setValue(valdb, dontSendNotification);

        val = ourProcessor->getParameter(GainAudioProcessor::overdrive);
        overdriveKnob->setValue(val * 100.f);

        val = ourProcessor->getParameter(GainAudioProcessor::distort);
        distortKnob->setValue(val * 100.f);

        overdriveToggle->setToggleState(false, dontSendNotification);
        if (ourProcessor->getParameter(GainAudioProcessor::overdriveon))
            overdriveToggle->setToggleState(true, dontSendNotification);

        val = ourProcessor->getParameter(GainAudioProcessor::distorttype) * 2;
        distortCombo->setSelectedItemIndex((int)val, dontSendNotification);

        float chorusDelayNorm = ourProcessor->getParameter(GainAudioProcessor::chorusDelay);
        delayChKnob->setValue(chorusDelayNorm * 50.f + 1.f, dontSendNotification);

        float chorusMixNorm = ourProcessor->getParameter(GainAudioProcessor::chorusMix);
        drywetKnob->setValue(chorusMixNorm * 100.f, dontSendNotification);

        ourProcessor->ClearUIUpdateFlag();
    }
//se schimba datele dorite intre elementele interfetei grafice si modulul “ourProcessor”
    counter++;
    levelLdb = round(10.f * log10f(ourProcessor->getParameter(GainAudioProcessor::levell)));
    levelRdb = round(10.f * log10f(ourProcessor->getParameter(GainAudioProcessor::levelr)));



    peakLdb = round(20.f * log10(ourProcessor->getParameter(GainAudioProcessor::peakl)));
    peakRdb = round(20.f * log10(ourProcessor->getParameter(GainAudioProcessor::peakr)));
    if (counter >= 21)
    {
        String peakString(peakLdb);
        peakString += String("  ");
        peakString += String(peakRdb);
        peakLabel->setText(peakString, dontSendNotification);
        counter = 0;
    }




    if (peakLdb < -60.f)
        peakLdb = -60;
    if (peakRdb < -60.f)
        peakRdb = -60;
    if (levelLdb < -60.f)
        levelLdb = -60;
    if (levelRdb < -60.f)
        levelRdb = -60;

    if (peakLdb > 0.f)
        peakLdb = 0.f;
    if (peakRdb < 0.f)
        peakRdb = 0.f;
    if (levelLdb < 0.f)
        levelLdb = 0.f;
    if (levelRdb < 0.f)
        levelRdb = 0.f;
    repaint();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="GainAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="GainAudioProcessor* ownerFilter" variableInitialisers="AudioProcessorEditor(ownerFilter)&#10;"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="1600" initialHeight="250">
  <BACKGROUND backgroundColour="ff24882f"/>
  <GROUPCOMPONENT name="Nonlinear Group" id="aeb9068ccc720f0" memberName="nonlineargroup"
                  virtualName="" explicitFocusOrder="0" pos="784 24 184 207" title="Nonlinear processing"/>
  <LABEL name="Peak Label" id="8babb4753b2ef65" memberName="peakLabel"
         virtualName="" explicitFocusOrder="0" pos="984 192 78 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Peak" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <GROUPCOMPONENT name="Compressor Group Box" id="2ce05e1c7292cc18" memberName="compressorGroupBox"
                  virtualName="" explicitFocusOrder="0" pos="264 88 488 143" title="Compressor"/>
  <SLIDER name="delay Knob" id="fcbae5966dfda7ed" memberName="delayKnob"
          virtualName="" explicitFocusOrder="0" pos="16 120 110 88" min="0.0"
          max="1000.0" int="1.0" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="Gain Slider " id="bdb749f08d967035" memberName="gainSlider"
          virtualName="" explicitFocusOrder="0" pos="64 12 271 16" tooltip="Regleaza nivelul"
          bkgcol="ff30393e" rotarysliderfill="ff05354a" min="-70.0" max="0.0"
          int="0.1" style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <LABEL name="Gain Label" id="37d6d2b0036c108e" memberName="gainLabel"
         virtualName="" explicitFocusOrder="0" pos="24 8 70 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Nivel dB&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="1" italic="0" justification="34"
         typefaceStyle="Bold"/>
  <SLIDER name="Freq Slider" id="b4328b766caeb910" memberName="frSlider"
          virtualName="" explicitFocusOrder="0" pos="120 32 150 24" min="20.0"
          max="20000.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="Freq Label" id="66f48fcafe37d2b9" memberName="frLabel"
         virtualName="" explicitFocusOrder="0" pos="8 32 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Frecventa(Hz)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="18.5" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="Delay Label" id="135a9f0caadc639c" memberName="delayLabel"
         virtualName="" explicitFocusOrder="0" pos="32 104 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Delay (ms)" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="Feedback Label" id="2e629b01218cd3ae" memberName="feedbackLabel"
         virtualName="" explicitFocusOrder="0" pos="128 104 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Feedback(dB)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="Threshold Label" id="43df169c1065d53d" memberName="thresholdLabel"
         virtualName="" explicitFocusOrder="0" pos="240 104 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Threshold [dB]" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <SLIDER name="Threshold Knob" id="d9f76aaa3151cb63" memberName="thresholdKnob"
          virtualName="" explicitFocusOrder="0" pos="240 120 134 88" min="-100.0"
          max="0.0" int="0.1" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="Ratio Knob" id="b512b691bcfa8796" memberName="ratioKnob"
          virtualName="" explicitFocusOrder="0" pos="340 120 110 88" min="1.0"
          max="20.0" int="0.1" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="Ratio Label" id="97bf18411bdbd17f" memberName="ratioLabel2"
         virtualName="" explicitFocusOrder="0" pos="320 104 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Ratio" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <SLIDER name="Attack Knob" id="6acd78e97c677981" memberName="attackKnob"
          virtualName="" explicitFocusOrder="0" pos="440 120 110 88" min="0.0"
          max="200.0" int="0.1" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="50" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="Attack Label" id="9539d704dbea6400" memberName="attackLabel"
         virtualName="" explicitFocusOrder="0" pos="416 104 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Attack [ms]" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <SLIDER name="Release Knob" id="2ef2fba467207f29" memberName="releaseKnob"
          virtualName="" explicitFocusOrder="0" pos="540 120 110 88" min="0.0"
          max="1000.0" int="0.1" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="50" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="Release Label" id="6f2e8bff24830537" memberName="releaseLabel"
         virtualName="" explicitFocusOrder="0" pos="520 104 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Release [ms]" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <SLIDER name="Makeup Knob" id="45f2581abff5298d" memberName="makeupKnob"
          virtualName="" explicitFocusOrder="0" pos="640 120 115 88" min="0.0"
          max="40.0" int="0.1" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="Makeup Label" id="18f2948db45d7cfc" memberName="makeupLabel"
         virtualName="" explicitFocusOrder="0" pos="624 104 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Makeup [dB]" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <SLIDER name="Feedback Knob" id="aa75c22f48ab00ad" memberName="feedbackKnob3"
          virtualName="" explicitFocusOrder="0" pos="112 120 126 88" min="-100.0"
          max="0.0" int="1.0" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <GROUPCOMPONENT name="new group" id="ac9a6711dee575a2" memberName="delayGroupBox"
                  virtualName="" explicitFocusOrder="0" pos="0 88 256 142" title="Delay Effect"/>
  <SLIDER name="Overdrive Knob" id="a23e56d18f2301d8" memberName="overdriveKnob"
          virtualName="" explicitFocusOrder="0" pos="776 64 115 88" min="0.0"
          max="100.0" int="1.0" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="Overdrive Label" id="64e6ee6bd3b3dbc5" memberName="overdriveLabel"
         virtualName="" explicitFocusOrder="0" pos="760 40 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Overdrive" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <SLIDER name="Distort Knob" id="39c14ad811b5ad6" memberName="distortKnob"
          virtualName="" explicitFocusOrder="0" pos="864 64 115 88" min="0.0"
          max="100.0" int="1.0" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="Distort Label" id="43dcfe7db87fc3b5" memberName="distortLabel"
         virtualName="" explicitFocusOrder="0" pos="848 40 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Distortion" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <TOGGLEBUTTON name="Overdrive Toggle" id="8ffc4f15294e5d2" memberName="overdriveToggle"
                virtualName="" explicitFocusOrder="0" pos="800 192 70 24" buttonText="Active"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <COMBOBOX name="Distort Combo" id="7b70379bc57f993" memberName="distortCombo"
            virtualName="" explicitFocusOrder="0" pos="832 160 126 24" editable="0"
            layout="33" items="Off&#10;Valve&#10;Synthetic" textWhenNonSelected=""
            textWhenNoItems="(no choices)"/>
  <SLIDER name="Delay Ch Knob" id="8ce425b5764f8e2c" memberName="delayChKnob"
          virtualName="" explicitFocusOrder="0" pos="1078 120 115 88" min="0.0"
          max="50.0" int="1.0" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="Delay Ch Label" id="231ca7283ebdad0f" memberName="delayChLabel"
         virtualName="" explicitFocusOrder="0" pos="1061 104 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Delay" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <SLIDER name="Dry Wet Knob" id="72ef322569b16b12" memberName="drywetKnob"
          virtualName="" explicitFocusOrder="0" pos="1184 118 115 88" min="0.0"
          max="100.0" int="1.0" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="Dry Wet Label" id="8be53a1d6e170be8" memberName="drywetLabel"
         virtualName="" explicitFocusOrder="0" pos="1167 102 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Dry/Wet" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <GROUPCOMPONENT name="new group" id="b4aec26c98dbede8" memberName="juce__groupComponent2"
                  virtualName="" explicitFocusOrder="0" pos="1096 88 200 150" title="group"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

