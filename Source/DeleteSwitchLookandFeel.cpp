/*
  ==============================================================================

    DeleteSwitchLook&Feel.cpp
    Created: 23 May 2023 8:43:04pm
    Author:  Iker

  ==============================================================================
*/

#include "DeleteSwitchLookandFeel.h"

DeleteSwitchLookandFeel::DeleteSwitchLookandFeel()
{
}

DeleteSwitchLookandFeel::~DeleteSwitchLookandFeel()
{
}

void DeleteSwitchLookandFeel::drawToggleButton(juce::Graphics& g, juce::ToggleButton& byPassSwitch, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    g.setColour(juce::Colours::transparentBlack);
    juce::Rectangle<float> roundedRectangleButton (byPassSwitch.getLocalBounds().toFloat());
    g.drawRoundedRectangle(roundedRectangleButton, 5.f, 9.f);
    g.setColour(juce::Colours::white);
    g.fillRoundedRectangle(roundedRectangleButton, 9.f);

    auto n = 0;
    juce::Line<float> diagLine1 (juce::Point<float>((roundedRectangleButton.getX()) + n, roundedRectangleButton.getY() + n), juce::Point<float>((roundedRectangleButton.getX()) + roundedRectangleButton.getWidth() - n, roundedRectangleButton.getY() + roundedRectangleButton.getHeight() - n));
    juce::Line<float> diagLine2(juce::Point<float>((roundedRectangleButton.getX()) + roundedRectangleButton.getWidth() + n, roundedRectangleButton.getY() + n), juce::Point<float>((roundedRectangleButton.getX() - n), roundedRectangleButton.getY() + roundedRectangleButton.getHeight() - n));
    g.setColour(juce::Colours::white.darker());
    g.drawLine(diagLine1, 1.0f);
    g.drawLine(diagLine2, 1.0f);
}