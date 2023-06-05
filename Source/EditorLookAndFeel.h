/*
  ==============================================================================

    EditorLookAndFeel.h
    Created: 14 May 2023 10:44:02am
    Author:  James Bedson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class EditorLookAndFeel  : public juce::LookAndFeel_V4
{
public:
    EditorLookAndFeel();
    ~EditorLookAndFeel() override;

    void drawRotarySlider(juce::Graphics&, int x, int y, int width, int height,
                           float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
                           juce::Slider&) override;
    void drawToggleButton(juce::Graphics&, juce::ToggleButton& toggle,
        bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EditorLookAndFeel)
};
