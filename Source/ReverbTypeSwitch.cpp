/*
  ==============================================================================

    ReverbTypeSwitch.cpp
    Created: 12 Jun 2023 5:00:36pm
    Author:  Iker

  ==============================================================================
*/

#include "ReverbTypeSwitch.h"

ReverbTypeSwitch::ReverbTypeSwitch()
{
    currentSetting = 0;
    setInterceptsMouseClicks(true, true);
}

ReverbTypeSwitch::~ReverbTypeSwitch()
{
}

void ReverbTypeSwitch::paint(juce::Graphics& g)
{
    juce::Rectangle<int> bounds = getLocalBounds();
    int settingWidth = bounds.getWidth() / 4;
    int settingHeight = bounds.getHeight();
    int switchHeight = 20;

    // Calculate the position and rectangle for the background rounded rectangle
    juce::Rectangle<int> backgroundRect(bounds.getX(), (settingHeight - switchHeight) / 2, bounds.getWidth(), switchHeight);
    g.setColour(juce::Colours::white);
    g.drawRoundedRectangle(backgroundRect.reduced(5.f, 2.f).toFloat(), 7.f, 1.2f);

    for (int i = 0; i < 4; ++i)
    {
        juce::Rectangle<int> settingRect(i * settingWidth, (settingHeight - switchHeight) / 2, settingWidth, switchHeight);
        if (i == currentSetting)
        {
            g.setColour(juce::Colours::white);
            g.fillRoundedRectangle(settingRect.reduced(6.f, 2.f).toFloat(), 7.f);
        }
    }
}

void ReverbTypeSwitch::mouseDown(const juce::MouseEvent& event)
{
    currentSetting = (currentSetting + 1) % 4;
    repaint();
}

int ReverbTypeSwitch::getCurrentSetting() const
{
    return currentSetting;
}