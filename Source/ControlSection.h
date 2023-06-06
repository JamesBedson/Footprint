/*
  ==============================================================================

    ControlSection.h
    Created: 6 May 2023 2:06:39pm
    Author:  James Bedson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "EditorLookAndFeel.h"
#include "GUIAttributes.h"

//==============================================================================
/*
*/

using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;

class ControlSection  : public juce::Component, public juce::Button::Listener
{
public:
    ControlSection(FootprintAudioProcessor* p);
    ~ControlSection() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void buttonClicked(juce::Button* button) override;

private:

    int sliderCol1CentreX;
    int sliderCol2CentreX;

    int sliderRow1CentreY;
    int sliderRow2CentreY;

    int sliderWidth, sliderHeight;
    int toggleWidth, toggleHeight;
    int sliderLabelWidth, sliderLabelHeight;
    int toggleLabelWidth, toggleLabelHeight;

    juce::Slider input, output;
    SliderAttachment inputAttachment, outputAttachment;
    
    std::vector<juce::Slider*> sliders {&input, &output};
    juce::Label inputLabel, outputLabel, switchLabel;
    std::vector<juce::Label*> sliderLabels{ &inputLabel, &outputLabel};
    
    juce::ToggleButton monoStereoSwitch;
    ButtonAttachment monoSwitchAttachment;
        
    void paintDecor(juce::Graphics&);

    EditorLookAndFeel lookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlSection)
};
