/*
  ==============================================================================

    ButtonLookAndFeel.h
    Created: 16 May 2023 2:59:59pm
    Author:  Pau Segalés Torres

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ButtonLookAndFeel  : public juce::LookAndFeel_V4
{
public:
    ButtonLookAndFeel();
    ~ButtonLookAndFeel() override;

    void drawToggleButton (juce::Graphics&, juce::ToggleButton&, bool shouldDrawButtonAsHighlighted,                      bool shouldDrawButtonAsDown) override;
    
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ButtonLookAndFeel)
};
