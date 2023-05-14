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
class EditorLookAndFeel  : public juce::Component
{
public:
    EditorLookAndFeel();
    ~EditorLookAndFeel() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EditorLookAndFeel)
};
