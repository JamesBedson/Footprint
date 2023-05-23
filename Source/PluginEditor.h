/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ControlSection.h"
#include "DisplaySection.h"
#include "PedalSection.h"
#include "LevelMeter.h"

//==============================================================================
/**
*/
class FootprintAudioProcessorEditor : public juce::AudioProcessorEditor, public juce::Timer
{
public:
    FootprintAudioProcessorEditor (FootprintAudioProcessor&);
    ~FootprintAudioProcessorEditor() override;

    //==============================================================================
    void timerCallback()                override;
    void paint (juce::Graphics&)        override;
    void resized()                      override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    
    DisplaySection              displaySection;
    PedalSection                pedalSection;
    ControlSection              controlSection;
    
    FootprintAudioProcessor&    audioProcessor;
    
    juce::Image                 background = juce::ImageCache::getFromMemory(BinaryData::backgroundPurpleBlue_png,
                                                                             BinaryData::backgroundPurpleBlue_pngSize);
    LevelMeter levelInMeterLeft, levelInMeterRight;
    LevelMeter levelOutMeterLeft, levelOutMeterRight;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FootprintAudioProcessorEditor)
};
