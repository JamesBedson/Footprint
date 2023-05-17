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
    for (auto* slider : sliders){
        slider->setLookAndFeel(nullptr);
    }
}

void ReverbPedal::paintAdditionalComponents(juce::Graphics& g)
{
    juce::Rectangle<int> textBounds = getLocalBounds().withY(getHeight() * -0.43f); // Adjust the vertical position here
    g.drawText ("ReverbPedal", textBounds,
                juce::Justification::centred, true);   // draw some placeholder text

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

void ReverbPedal::paintBackground(juce::Graphics& g){
    
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
    g.setColour(juce::Colours::hotpink);
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 15.0f, 1.0f);
    g.setColour(juce::Colours::hotpink);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 15.0f);
    g.setColour(juce::Colours::white);
    g.setFont(14.0f);
    */
}
