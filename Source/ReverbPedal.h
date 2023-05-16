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
#include "PedalLookAndFeel.h"

//==============================================================================
/*
*/
class ReverbPedal  : public Pedal
{
public:
    ReverbPedal();
    ~ReverbPedal()                  override;

    void paintChild(juce::Graphics&)    override;
    void resizeChild()              override;

private:

    juce::Slider mix, highCut, lowCut, type;
    std::vector<juce::Slider*> sliders {&mix, &highCut, &lowCut, &type};
    
    juce::Label mixLabel, highCutLabel, lowCutLabel, typeLabel;
    std::vector<juce::Label*> sliderLabels{ &mixLabel, &highCutLabel, &lowCutLabel, &typeLabel };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbPedal)
};
