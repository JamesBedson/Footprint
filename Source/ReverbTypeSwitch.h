/*
  ==============================================================================

    ReverbTypeSwitch.h
    Created: 12 Jun 2023 5:00:36pm
    Author:  Iker

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


class ReverbTypeSwitch : public juce::Component
{
public:
    ReverbTypeSwitch();
    ~ReverbTypeSwitch()                                 override;

    void paint(juce::Graphics&)                         override;
    void mouseDown(const juce::MouseEvent& event)       override;
    int getCurrentSetting() const;

private:
    int currentSetting;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ReverbTypeSwitch)

};