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
class FootprintAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    FootprintAudioProcessorEditor (FootprintAudioProcessor&);
    ~FootprintAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&)        override;
    void resized()                      override;


private:
    
    FootprintAudioProcessor&    audioProcessor;
    
    DisplaySection              displaySection;
    PedalSection                pedalSection;
    ControlSection              controlSection;
    
    juce::Image                 background = juce::ImageCache::getFromMemory(BinaryData::backgroundPurpleBlue_png,
                                                                             BinaryData::backgroundPurpleBlue_pngSize);

    void paintDecor(juce::Graphics&);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FootprintAudioProcessorEditor)
};
