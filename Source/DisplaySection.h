/*
  ==============================================================================

    DisplaySection.h
    Created: 6 May 2023 2:11:16pm
    Author:  James Bedson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "WaveformVisualizer.h"

//==============================================================================
/*
*/
class DisplaySection  : public juce::Component
{
public:
    DisplaySection();
    ~DisplaySection() override;
    
    void paint (juce::Graphics&) override;
    void resized() override;
    
    juce::Image displayBackground = juce::ImageCache::getFromMemory(BinaryData::DisplayPanel_png, BinaryData::DisplayPanel_pngSize);
    
    WaveformVisualizer inputWaveform, outputWaveform;

    juce::Slider bufferSizeView;
    juce::Slider WaveformZoom;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DisplaySection)
};
