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
    DistortionPedal(FootprintAudioProcessor* processor,
                    juce::StringArray parameterIDs,
                    const int& pedalSlot);
    
    ~DistortionPedal()                                  override;

    void paintBackground(juce::Graphics&)               override;
    void paintAdditionalComponents(juce::Graphics&)     override;
    void resizeChild()                                  override;

private:
    
    FootprintAudioProcessor* p;
    
    juce::Slider tone, gain, level;
    std::vector<juce::Slider*> sliders {&tone, &gain, &level};
    
    SliderAttachment gainAttachment, levelAttachment, toneAttachment;
    
    juce::Label toneLabel, gainLabel, levelLabel;
    std::vector<juce::Label*> sliderLabels {&toneLabel, &gainLabel, &levelLabel};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionPedal)
};
