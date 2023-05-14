/*
  ==============================================================================

    EnvelopePedal.h
    Created: 14 May 2023 10:43:40am
    Author:  James Bedson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class EnvelopePedal  : public juce::Component
{
public:
    EnvelopePedal();
    ~EnvelopePedal() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopePedal)
};
