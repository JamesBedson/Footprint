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
    
    juce::Font labelFont;
    labelFont.setTypefaceName("Futura");
    labelFont.setHeight(GUIAttributes::PedalFontSizes::h2);
    qualityFactorLabel.setFont(labelFont);
    sensitivityLabel.setFont(labelFont);
    cutoffThresholdLabel.setFont(labelFont);

    qualityFactorLabel.setText      ("Q", juce::dontSendNotification);
    sensitivityLabel.setText      ("Sensitivity", juce::dontSendNotification);
    cutoffThresholdLabel.setText     ("Cutoff", juce::dontSendNotification);
}

EnvelopePedal::~EnvelopePedal()
{
    for (auto* slider : sliders){
        slider->setLookAndFeel(nullptr);
    }
}

void EnvelopePedal::paintBackground(juce::Graphics& g){
    
    if (slot == 1){
        g.drawImage(backgroundSlot1, getLocalBounds().toFloat(), juce::RectanglePlacement::stretchToFit);
    } else if (slot == 2){
        g.drawImage(backgroundSlot2, getLocalBounds().toFloat(), juce::RectanglePlacement::stretchToFit);
    } else if (slot == 3){
        g.drawImage(backgroundSlot3, getLocalBounds().toFloat(), juce::RectanglePlacement::stretchToFit);
    } else if (slot == 4){
        g.drawImage(backgroundSlot3, getLocalBounds().toFloat(), juce::RectanglePlacement::stretchToFit);
    } else {
        return;
    }
}


void EnvelopePedal::paintAdditionalComponents(juce::Graphics& g)
{
    juce::Rectangle<int> textBounds = getLocalBounds().withY(getHeight() * -0.38f);

    juce::Font font;
    font.setTypefaceName("Futura");
    font.setHeight(GUIAttributes::PedalFontSizes::h1);
    g.setFont(font); // Set the updated font

    g.drawText ("ENVELOPE FILTER", textBounds,
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
