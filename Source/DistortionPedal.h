/*
  ==============================================================================

    DistortionPedal.h
    Created: 14 May 2023 10:43:31am
    Author:  James Bedson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class DistortionPedal  : public juce::Component
{
public:
    DistortionPedal();
    ~DistortionPedal() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionPedal)
};
