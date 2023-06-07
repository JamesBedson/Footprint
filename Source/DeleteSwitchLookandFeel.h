/*
  ==============================================================================

    DeleteSwitchLook&Feel.h
    Created: 23 May 2023 8:43:04pm
    Author:  Iker

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class DeleteSwitchLookandFeel : public juce::LookAndFeel_V4
{
public:
    DeleteSwitchLookandFeel();
    ~DeleteSwitchLookandFeel() override;

    void drawToggleButton(juce::Graphics&, juce::ToggleButton&, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeleteSwitchLookandFeel)
};
