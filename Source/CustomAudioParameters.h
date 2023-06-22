/*
  ==============================================================================

    CustomAudioParameters.h
    Created: 22 Jun 2023 6:36:41pm
    Author:  James Bedson

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class NonAutomatableParameterChoice: public juce::AudioParameterChoice{
public:
    NonAutomatableParameterChoice(const juce::ParameterID& parameterID,
                                  const juce::String& parameterName,
                                  const juce::StringArray& choices,
                                  const int& defaultIdx) : juce::AudioParameterChoice(parameterID,
                                                                                          parameterName,
                                                                                          choices,
                                                                                          defaultIdx)
    {
        //
    }
    
    bool isAutomatable() const override { return false; }
    bool isMetaParameter() const override { return true; }
};
