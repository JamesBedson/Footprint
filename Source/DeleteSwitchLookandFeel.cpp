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
    g.drawRoundedRectangle(byPassSwitch.getLocalBounds().toFloat(), 5.f, 8.f);
    g.setColour(juce::Colours::white);
    g.fillRoundedRectangle(byPassSwitch.getLocalBounds().toFloat(), 8.f);

    juce::Line<float> diagLine1 (juce::Point<float>((byPassSwitch.getLocalBounds().getX() + 2.f), byPassSwitch.getLocalBounds().getY()), juce::Point<float>((byPassSwitch.getLocalBounds().getX()) + byPassSwitch.getLocalBounds().getWidth(), byPassSwitch.getLocalBounds().getY() + byPassSwitch.getLocalBounds().getHeight()));
    juce::Line<float> diagLine2(juce::Point<float>((byPassSwitch.getLocalBounds().getX() + 2.f) + byPassSwitch.getLocalBounds().getWidth(), byPassSwitch.getLocalBounds().getY()), juce::Point<float>((byPassSwitch.getLocalBounds().getX()), byPassSwitch.getLocalBounds().getY() + byPassSwitch.getLocalBounds().getHeight()));
    g.setColour(juce::Colours::white.darker());
    g.drawLine(diagLine1, 1.0f);
    g.drawLine(diagLine2, 1.0f);
}