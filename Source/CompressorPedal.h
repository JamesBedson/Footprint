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
    CompressorPedal(FootprintAudioProcessor* processor, juce::StringArray parameterIDs);
    ~CompressorPedal()                                  override;

    void paintBackground(juce::Graphics&)               override;
    void paintAdditionalComponents(juce::Graphics&)     override;
    void resizeChild()                                  override;

private:

    juce::Slider ratio, threshold, attack, release;
    std::vector<juce::Slider*> sliders {&ratio, &threshold, &attack, &release};
    
    SliderAttachment attackAttachment, releaseAttachment, thresholdAttachment, ratioAttachment;
    
    juce::Label ratioLabel, thresholdLabel, attackLabel, releaseLabel;
    std::vector<juce::Label*> sliderLabels {&ratioLabel, &thresholdLabel, &attackLabel, &releaseLabel};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorPedal)
};
