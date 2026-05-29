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

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class GainAudioProcessorEditor  : public AudioProcessorEditor,
                                  public Timer,
                                  public juce::Slider::Listener,
                                  public juce::Button::Listener,
                                  public juce::ComboBox::Listener
{
public:
    //==============================================================================
    GainAudioProcessorEditor (GainAudioProcessor* ownerFilter);
    ~GainAudioProcessorEditor() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void timerCallback();
        GainAudioProcessor* getProcessor() const
    {
     return static_cast
        <GainAudioProcessor*>(getAudioProcessor());
    }
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    float levelLdb, levelRdb, peakLdb, peakRdb;
    int counter;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::GroupComponent> nonlineargroup;
    std::unique_ptr<juce::Label> peakLabel;
    std::unique_ptr<juce::GroupComponent> compressorGroupBox;
    std::unique_ptr<juce::Slider> delayKnob;
    std::unique_ptr<juce::Slider> gainSlider;
    std::unique_ptr<juce::Label> gainLabel;
    std::unique_ptr<juce::Slider> frSlider;
    std::unique_ptr<juce::Label> frLabel;
    std::unique_ptr<juce::Label> delayLabel;
    std::unique_ptr<juce::Label> feedbackLabel;
    std::unique_ptr<juce::Label> thresholdLabel;
    std::unique_ptr<juce::Slider> thresholdKnob;
    std::unique_ptr<juce::Slider> ratioKnob;
    std::unique_ptr<juce::Label> ratioLabel2;
    std::unique_ptr<juce::Slider> attackKnob;
    std::unique_ptr<juce::Label> attackLabel;
    std::unique_ptr<juce::Slider> releaseKnob;
    std::unique_ptr<juce::Label> releaseLabel;
    std::unique_ptr<juce::Slider> makeupKnob;
    std::unique_ptr<juce::Label> makeupLabel;
    std::unique_ptr<juce::Slider> feedbackKnob3;
    std::unique_ptr<juce::GroupComponent> delayGroupBox;
    std::unique_ptr<juce::Slider> overdriveKnob;
    std::unique_ptr<juce::Label> overdriveLabel;
    std::unique_ptr<juce::Slider> distortKnob;
    std::unique_ptr<juce::Label> distortLabel;
    std::unique_ptr<juce::ToggleButton> overdriveToggle;
    std::unique_ptr<juce::ComboBox> distortCombo;
    std::unique_ptr<juce::Slider> delayChKnob;
    std::unique_ptr<juce::Label> delayChLabel;
    std::unique_ptr<juce::Slider> drywetKnob;
    std::unique_ptr<juce::Label> drywetLabel;
    std::unique_ptr<juce::GroupComponent> juce__groupComponent2;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

