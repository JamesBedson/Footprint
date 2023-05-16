/*
  ==============================================================================

    CompressorPedal.cpp
    Created: 14 May 2023 10:42:45am
    Author:  James Bedson

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CompressorPedal.h"

//==============================================================================
CompressorPedal::CompressorPedal()
{
    for (auto& slider : sliders) {
        addAndMakeVisible(slider);
        slider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        slider->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
        slider->setLookAndFeel(&pedalLookAndFeel);

    }
    
    for (auto& label : sliderLabels){
        addAndMakeVisible(label);
        label->setJustificationType(juce::Justification::horizontallyCentred);
    }
    
    thresholdLabel.attachToComponent    (&threshold, false);
    ratioLabel.attachToComponent        (&ratio, false);
    attackLabel.attachToComponent       (&attack, false);
    releaseLabel.attachToComponent      (&release, false);
    
    thresholdLabel.setText  ("Threshold", juce::dontSendNotification);
    ratioLabel.setText      ("Ratio", juce::dontSendNotification);
    attackLabel.setText     ("Attack", juce::dontSendNotification);
    releaseLabel.setText    ("Release", juce::dontSendNotification);
    
}

CompressorPedal::~CompressorPedal()
{
    for (auto* slider : sliders){
        slider->setLookAndFeel(nullptr);
    }
}

void CompressorPedal::paintChild(juce::Graphics& g)
{
    g.setColour(juce::Colours::sandybrown);
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 15.0f, 1.0f);
    g.setColour(juce::Colours::sandybrown);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 15.0f);
    g.setColour(juce::Colours::white);
    g.setFont(14.0f);

    juce::Rectangle<int> textBounds = getLocalBounds().withY(getHeight() * -0.43f); // Adjust the vertical position here
    g.drawText("CompressorPedal", textBounds,
        juce::Justification::centred, true);   // draw some placeholder text
}

void CompressorPedal::resizeChild(){
    
    for (auto& slider : sliders){
        slider->setSize(sliderWidth, sliderHeight);
    }
    
    threshold.setCentrePosition (sliderCol1CentreX, sliderRow1CentreY);
    ratio.setCentrePosition     (sliderCol1CentreX, sliderRow2CentreY);
    attack.setCentrePosition    (sliderCol3CentreX, sliderRow1CentreY);
    release.setCentrePosition   (sliderCol3CentreX, sliderRow2CentreY);
    
    for (auto& label : sliderLabels){
        
        auto sliderBounds   = label->getAttachedComponent()->getBounds();
        auto bottomX        = sliderBounds.getBottomLeft().getX();
        auto bottomY        = sliderBounds.getBottomLeft().getY();
        
        label->setBounds(bottomX, bottomY, sliderLabelWidth, sliderLabelHeight);
        
    }
    
}
