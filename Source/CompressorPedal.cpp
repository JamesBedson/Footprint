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

void CompressorPedal::paintAdditionalComponents(juce::Graphics& g)
{
    juce::Rectangle<int> textBounds = getLocalBounds().withY(getHeight() * -0.43f); 
    g.drawText("CompressorPedal",
               textBounds,
               juce::Justification::centred, true);
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

void CompressorPedal::paintBackground(juce::Graphics &g){
    
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
    
    /*
    g.setColour(juce::Colours::sandybrown);
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 15.0f, 1.0f);
    g.setColour(juce::Colours::sandybrown);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 15.0f);
    g.setColour(juce::Colours::white);
    g.setFont(14.0f);*/

    
}
