/*
  ==============================================================================

    ControlSection.h
    Created: 6 May 2023 2:06:39pm
    Author:  James Bedson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ControlSection  : public juce::Component
{
public:
    ControlSection();
    ~ControlSection() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlSection)
};
