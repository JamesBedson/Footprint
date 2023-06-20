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
#include "ReverbTypeSwitch.h"

//==============================================================================
/*
*/
class ReverbPedal  : public Pedal, public juce::Timer
{
public:
    ReverbPedal(FootprintAudioProcessor* processor,
                juce::StringArray parameterIDs,
                const int& pedalSlot);
    
    ~ReverbPedal()                                      override;

    void paintBackground(juce::Graphics&)               override;
    void paintAdditionalComponents(juce::Graphics&)     override;
    void paint(juce::Graphics& g)                       override;
    void resizeChild()                                  override;
    void timerCallback()                                override;

private:
    
    FootprintAudioProcessor* p;
    
    juce::Slider mix;
    ReverbTypeSwitch reverbTypeSwitch;
    juce::Value irSetting;
    
    //std::vector<juce::Slider*> sliders {&mix, &highCut, &lowCut};
    //SliderAttachment mixAttachment, lowpassAttachment, highpassAttachment;
    std::vector<juce::Slider*> sliders{ &mix};
    SliderAttachment mixAttachment;
    juce::Value impulseResponseChoice;
    
    //juce::Label mixLabel, highCutLabel, lowCutLabel, typeLabel;
    //std::vector<juce::Label*> sliderLabels{ &mixLabel, &highCutLabel, &lowCutLabel, &typeLabel};
    juce::Label mixLabel, typeLabel;
    std::vector<juce::Label*> sliderLabels{ &mixLabel, &typeLabel };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbPedal)
};
