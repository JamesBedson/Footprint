/*
  ==============================================================================

    ControlSection.h
    Created: 6 May 2023 2:06:39pm
    Author:  James Bedson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "EditorLookAndFeel.h"

//==============================================================================
/*
*/
class ControlSection  : public juce::Component
{
public:
    ControlSection();
    ~ControlSection() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    int sliderCol1CentreX;
    int sliderCol2CentreX;

    int sliderRow1CentreY;
    int sliderRow2CentreY;

    int sliderWidth, sliderHeight;
    int sliderLabelWidth, sliderLabelHeight;

    juce::Slider input, output;
    std::vector<juce::Slider*> sliders{&input, &output};
    juce::Label inputLabel, outputLabel;
    std::vector<juce::Label*> sliderLabels{ &inputLabel, &outputLabel};
    
    EditorLookAndFeel lookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlSection)
};
