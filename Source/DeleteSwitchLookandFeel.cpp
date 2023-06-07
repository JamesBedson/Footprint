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

    int centerX = roundedRectangleButton.getWidth() / 2;
    int centerY = roundedRectangleButton.getHeight() / 2;
    int radius = std::min(roundedRectangleButton.getWidth(), roundedRectangleButton.getHeight()) / 2;
    int startX = centerX - radius;
    int startY = centerY - radius;
    int endX = centerX + radius;
    int endY = centerY + radius;

    g.setColour(juce::Colours::white.darker().darker());

    float n = 1.1f;
    g.drawLine(startX + n, startY + n, endX - n, endY - n);
    g.drawLine(startX + n, endY - n, endX - n, startY + n);
}