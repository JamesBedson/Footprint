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

    juce::Line<float> diagLine1 (juce::Point<float>((roundedRectangleButton.getX()), roundedRectangleButton.getY()), juce::Point<float>((roundedRectangleButton.getX()) + roundedRectangleButton.getWidth(), roundedRectangleButton.getY() + roundedRectangleButton.getHeight()));
    juce::Line<float> diagLine2(juce::Point<float>((roundedRectangleButton.getX()) + roundedRectangleButton.getWidth(), roundedRectangleButton.getY()), juce::Point<float>((roundedRectangleButton.getX()), roundedRectangleButton.getY() + roundedRectangleButton.getHeight()));
    g.setColour(juce::Colours::white.darker());
    g.drawLine(diagLine1, 1.0f);
    g.drawLine(diagLine2, 1.0f);
}