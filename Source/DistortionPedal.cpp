/*
  ==============================================================================

    DistortionPedal.cpp
    Created: 14 May 2023 10:43:31am
    Author:  James Bedson

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DistortionPedal.h"

//==============================================================================
DistortionPedal::DistortionPedal()
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
    
    toneLabel.attachToComponent    (&tone, false);
    gainLabel.attachToComponent    (&gain, false);
    levelLabel.attachToComponent   (&level, false);
    
    gainLabel.setText      ("Gain", juce::dontSendNotification);
    toneLabel.setText      ("Tone", juce::dontSendNotification);
    levelLabel.setText     ("Level", juce::dontSendNotification);
}

DistortionPedal::~DistortionPedal()
{
    for (auto* slider : sliders){
        slider->setLookAndFeel(nullptr);
    }
}

void DistortionPedal::paintChild(juce::Graphics& g)
{
    g.setColour(juce::Colours::lightseagreen);
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 15.0f, 1.0f);
    g.setColour(juce::Colours::lightseagreen);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 15.0f);
    g.setColour(juce::Colours::white);
    g.setFont(14.0f);

    juce::Rectangle<int> textBounds = getLocalBounds().withY(getHeight() * -0.43f); // Adjust the vertical position here
    g.drawText("DistortionPedal", textBounds,
        juce::Justification::centred, true);   // draw some placeholder text

    juce::Rectangle<int> topLeft, topRigth, bottomCenter;
    auto rectWidth = 10;
    auto rectHeight = 10;

    topLeft.setSize(rectWidth, rectHeight);
    topLeft.setCentre(sliderCol1CentreX, sliderRow1CentreY);

    topRigth.setSize(rectWidth, rectHeight);
    topRigth.setCentre(sliderCol3CentreX, sliderRow1CentreY);

    bottomCenter.setSize(rectWidth, rectHeight);
    bottomCenter.setCentre(sliderCol2CentreX, sliderRow2CentreY);
}


void DistortionPedal::resizeChild()
{
    for (auto& slider : sliders)
    {
        slider->setSize(sliderWidth, sliderHeight);
    }

    tone.setCentrePosition(sliderCol1CentreX, sliderRow1CentreY);
    level.setCentrePosition(sliderCol2CentreX, sliderRow2CentreY);
    gain.setCentrePosition(sliderCol3CentreX, sliderRow1CentreY);
    
    for (auto& label : sliderLabels){
        
        auto sliderBounds   = label->getAttachedComponent()->getBounds();
        auto bottomX        = sliderBounds.getBottomLeft().getX();
        auto bottomY        = sliderBounds.getBottomLeft().getY();
        
        label->setBounds(bottomX, bottomY, sliderLabelWidth, sliderLabelHeight);
    }
}
