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
    ReverbPedal(FootprintAudioProcessor* processor, juce::StringArray parameterIDs);
    ~ReverbPedal()                                      override;

    void paintBackground(juce::Graphics&)               override;
    void paintAdditionalComponents(juce::Graphics&)     override;
    void resizeChild()                                  override;

private:

    juce::Slider mix, highCut, lowCut, type;
    std::vector<juce::Slider*> sliders {&mix, &highCut, &lowCut, &type};
    
    SliderAttachment mixAttachment, lowpassAttachment, highpassAttachment;
    
    juce::Label mixLabel, highCutLabel, lowCutLabel, typeLabel;
    std::vector<juce::Label*> sliderLabels{ &mixLabel, &highCutLabel, &lowCutLabel, &typeLabel };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbPedal)
};
