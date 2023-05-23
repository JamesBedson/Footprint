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
    

    juce::Font labelFont;
    labelFont.setTypefaceName("Futura");
    labelFont.setHeight(GUIAttributes::PedalFontSizes::h2);
    gainLabel.setFont(labelFont);
    toneLabel.setFont(labelFont);
    levelLabel.setFont(labelFont);

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

void DistortionPedal::paintAdditionalComponents(juce::Graphics& g)
{
    juce::Rectangle<int> textBounds = getLocalBounds().withY(getHeight() * -0.38f);

    juce::Font font;
    font.setTypefaceName("Futura");
    font.setHeight(GUIAttributes::PedalFontSizes::h1);
    g.setFont(font); // Set the updated font

    g.drawText("DISTORTION", textBounds,
        juce::Justification::centred, true);
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

void DistortionPedal::paintBackground(juce::Graphics& g){
    
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
    g.setColour(juce::Colours::lightseagreen);
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 15.0f, 1.0f);
    g.setColour(juce::Colours::lightseagreen);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 15.0f);
    g.setColour(juce::Colours::white);
    g.setFont(14.0f);*/
}
