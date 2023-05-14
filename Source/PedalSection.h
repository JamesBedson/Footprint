/*
  ==============================================================================

    PedalSection.h
    Created: 6 May 2023 2:06:57pm
    Author:  James Bedson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Pedal.h"
#include "CompressorPedal.h"
#include "ReverbPedal.h"
#include "EnvelopePedal.h"
#include "DistortionPedal.h"

//==============================================================================
/*
*/
class PedalSection  : public juce::Component
{
public:
    PedalSection();
    ~PedalSection() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PedalSection)
    
    Pedal pedal;
    CompressorPedal CompressorPedal;
    ReverbPedal ReverbPedal;
    EnvelopePedal EnvelopePedal;
    DistortionPedal DistortionPedal;
};
