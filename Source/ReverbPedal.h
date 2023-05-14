/*
  ==============================================================================

    ReverbPedal.h
    Created: 14 May 2023 10:42:54am
    Author:  James Bedson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Pedal.h"

//==============================================================================
/*
*/
class ReverbPedal  : public Pedal
{
public:
    ReverbPedal();
    ~ReverbPedal() override;

    void paint (juce::Graphics&) override;
    //void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbPedal)
};