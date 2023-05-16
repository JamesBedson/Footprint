/*
  ==============================================================================

    ReverbPedal.cpp
    Created: 14 May 2023 10:42:54am
    Author:  James Bedson

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ReverbPedal.h"

//==============================================================================
ReverbPedal::ReverbPedal()
{
    for (auto& slider : sliders){
        addAndMakeVisible(slider);
        slider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        slider->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0,0);
        slider->setLookAndFeel(&pedalLookAndFeel);
    }
    for (auto& label : sliderLabels) {
        addAndMakeVisible(label);
        label->setJustificationType(juce::Justification::horizontallyCentred);
    }
    type.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);

    mixLabel.attachToComponent(&mix, false);
    highCutLabel.attachToComponent(&highCut, false);
    lowCutLabel.attachToComponent(&lowCut, false);
    typeLabel.attachToComponent(&type, false);

    mixLabel.setText("Mix", juce::dontSendNotification);
    highCutLabel.setText("H.Cut", juce::dontSendNotification);
    lowCutLabel.setText("L.Cut", juce::dontSendNotification);;
    typeLabel.setText("Type", juce::dontSendNotification);
}

ReverbPedal::~ReverbPedal()
{
}

void ReverbPedal::paintChild(juce::Graphics& g)
{

    g.setColour(juce::Colours::hotpink);
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 15.0f, 1.0f);
    g.setColour(juce::Colours::hotpink);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 15.0f);
    g.setColour(juce::Colours::white);
    g.setFont(14.0f);

    juce::Rectangle<int> textBounds = getLocalBounds().withY(getHeight() * -0.43f); // Adjust the vertical position here
    g.drawText ("ReverbPedal", textBounds,
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

void ReverbPedal::resizeChild(){
    
    for (auto& slider : sliders){
        if (slider != &type){
            slider->setSize(sliderWidth, sliderHeight);
        }
        else type.setSize(150, 50);
    }
    
    mix.setCentrePosition       (sliderCol2CentreX, sliderRow2CentreY);
    highCut.setCentrePosition   (sliderCol3CentreX, sliderRow1CentreY);
    lowCut.setCentrePosition    (sliderCol1CentreX, sliderRow1CentreY);
    type.setCentrePosition      (sliderCol2CentreX, sliderRow3CentreY);
    
    for (auto& label : sliderLabels) {

        auto sliderBounds   = label->getAttachedComponent()->getBounds();
        auto bottomX        = sliderBounds.getBottomLeft().getX();
        auto bottomY        = sliderBounds.getBottomLeft().getY();

        label->setBounds(bottomX, bottomY, sliderLabelWidth, sliderLabelHeight);
    }
}
