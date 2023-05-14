/*
  ==============================================================================

    Pedal.h
    Created: 14 May 2023 10:42:34am
    Author:  James Bedson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Pedal  : public juce::Component
{
public:
    Pedal();
    ~Pedal() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Pedal)
};
