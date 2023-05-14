/*
  ==============================================================================

    PedalLookAndFeel.h
    Created: 14 May 2023 10:43:50am
    Author:  James Bedson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PedalLookAndFeel  : public juce::Component
{
public:
    PedalLookAndFeel();
    ~PedalLookAndFeel() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PedalLookAndFeel)
};
