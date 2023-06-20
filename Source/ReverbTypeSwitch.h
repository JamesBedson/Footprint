/*
  ==============================================================================

    ReverbTypeSwitch.h
    Created: 12 Jun 2023 5:00:36pm
    Author:  Iker

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUIAttributes.h"

class ReverbTypeSwitch : public juce::Component
{
public:
    ReverbTypeSwitch(FootprintAudioProcessor* p, const std::string& );
    ~ReverbTypeSwitch()                                 override;

    void paint(juce::Graphics&)                         override;
    void mouseDown(const juce::MouseEvent& event)       override;
    int getCurrentSetting() const;
    void parameterChanged(float newValue);

    bool currentSettingChanged;
private:
    juce::ParameterAttachment choiceAttachment;
    int currentSetting;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ReverbTypeSwitch)

};
