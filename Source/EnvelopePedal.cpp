/*
  ==============================================================================

    EnvelopePedal.cpp
    Created: 14 May 2023 10:43:40am
    Author:  James Bedson

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EnvelopePedal.h"

//==============================================================================
EnvelopePedal::EnvelopePedal()
{
    for (auto& slider : sliders){
        addAndMakeVisible(slider);
        slider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        slider->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
        slider->setLookAndFeel(&pedalLookAndFeel);

    }
    
    for (auto& label : sliderLabels){
        addAndMakeVisible(label);
        label->setJustificationType(juce::Justification::horizontallyCentred);
    }
    
    qualityFactorLabel.attachToComponent    (&qualityFactor, false);
    sensitivityLabel.attachToComponent    (&sensitivity, false);
    cutoffThresholdLabel.attachToComponent   (&cutoffThreshold, false);
    
    qualityFactorLabel.setText      ("QualityFactor", juce::dontSendNotification);
    sensitivityLabel.setText      ("Sensitivity", juce::dontSendNotification);
    cutoffThresholdLabel.setText     ("CutoffThreshold", juce::dontSendNotification);
}

EnvelopePedal::~EnvelopePedal()
{
}

void EnvelopePedal::paintChild(juce::Graphics& g)
{

    g.setColour(juce::Colours::indianred);
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 15.0f, 1.0f);
    g.setColour(juce::Colours::indianred);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 15.0f);
    g.setColour(juce::Colours::white);
    g.setFont(14.0f);

    juce::Rectangle<int> textBounds = getLocalBounds().withY(getHeight() * -0.43f); // Adjust the vertical position here
    g.drawText ("EnvelopePedal", textBounds,
                juce::Justification::centred, true);   // draw some placeholder text
}

void EnvelopePedal::resizeChild(){
    
    for (auto& slider : sliders){
        slider->setSize(sliderWidth, sliderHeight);
    }
    
    sensitivity.setCentrePosition(sliderCol1CentreX, sliderRow1CentreY);
    qualityFactor.setCentrePosition(sliderCol2CentreX, sliderRow2CentreY);
    cutoffThreshold.setCentrePosition(sliderCol3CentreX, sliderRow1CentreY);
    
    for (auto& label : sliderLabels){
        
        auto sliderBounds   = label->getAttachedComponent()->getBounds();
        auto bottomX        = sliderBounds.getBottomLeft().getX();
        auto bottomY        = sliderBounds.getBottomLeft().getY();
        
        label->setBounds(bottomX, bottomY, sliderLabelWidth, sliderLabelHeight);
    }
}

