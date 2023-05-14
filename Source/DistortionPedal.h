/*
  ==============================================================================

    DistortionPedal.h
    Created: 14 May 2023 10:43:31am
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
class DistortionPedal  : public Pedal
{
public:
    DistortionPedal();
    ~DistortionPedal() override;

    void paint (juce::Graphics&) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionPedal)
};
