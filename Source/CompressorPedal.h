/*
  ==============================================================================

    CompressorPedal.h
    Created: 14 May 2023 10:42:45am
    Author:  James Bedson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class CompressorPedal  : public juce::Component
{
public:
    CompressorPedal();
    ~CompressorPedal() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorPedal)
};
