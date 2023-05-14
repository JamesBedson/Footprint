/*
  ==============================================================================

    CompressorPedal.h
    Created: 14 May 2023 10:42:45am
    Author:  James Bedson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Pedal.h"
#include "PedalLookAndFeel.h"

//==============================================================================
/*
*/
class CompressorPedal : public Pedal
{
public:
    CompressorPedal();
    ~CompressorPedal() override;

    void paint (juce::Graphics&) override;

private:

    juce::Slider ratio, threshold, attack, release;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorPedal)
};
