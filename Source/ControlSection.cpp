/*
  ==============================================================================

    ControlSection.cpp
    Created: 6 May 2023 2:06:39pm
    Author:  James Bedson

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ControlSection.h"

//==============================================================================
ControlSection::ControlSection()
{
    for (auto& slider : sliders) {
        addAndMakeVisible(slider);
        slider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        slider->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
        slider->setLookAndFeel(&lookAndFeel);
    }

    for (auto& label : sliderLabels) {
        addAndMakeVisible(label);
        label->setJustificationType(juce::Justification::horizontallyCentred);
    }

    inputLabel.attachToComponent(&input, false);
    outputLabel.attachToComponent(&output, false);

    inputLabel.setText("Input", juce::dontSendNotification);
    outputLabel.setText("Output", juce::dontSendNotification);
}

ControlSection::~ControlSection()
{
    for (auto* slider : sliders){
        slider->setLookAndFeel(nullptr);
    }
}

void ControlSection::paint (juce::Graphics& g)
{
    /*
    g.setColour(juce::Colours::royalblue);
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 15.0f, 1.0f);
    g.setColour(juce::Colours::royalblue);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 15.0f);*/
    g.setColour (juce::Colours::white);
    g.setFont (25.0f);
    juce::Rectangle<int> textBounds = getLocalBounds().withY(getHeight() * -0.39f); // Adjust the vertical position here
    g.drawText ("FOOTPRINT", textBounds,
                juce::Justification::centred, true);   // draw some placeholder text
}

void ControlSection::resized()
{
    auto bounds       = getBounds();
    auto width        = getWidth();
    auto height       = getHeight();
    sliderCol1CentreX = getX() + width * 0.29f;
    sliderRow1CentreY = getY() + height * 0.33f;
    sliderCol2CentreX = getX() + width * 0.71f;
    sliderRow2CentreY = getY() + height * 0.7f;

    sliderWidth       = 80;
    sliderHeight      = 80;

    sliderLabelWidth  = sliderWidth;
    sliderLabelHeight = 15;

    for (auto& slider : sliders) {
        slider->setSize(sliderWidth, sliderHeight);
    }

    input.setCentrePosition(sliderCol1CentreX, sliderRow1CentreY);
    output.setCentrePosition(sliderCol2CentreX, sliderRow2CentreY);

    for (auto& label : sliderLabels) {

        auto sliderBounds = label->getAttachedComponent()->getBounds();
        auto bottomX = sliderBounds.getBottomLeft().getX();
        auto bottomY = sliderBounds.getBottomLeft().getY();

        label->setBounds(bottomX, bottomY, sliderLabelWidth, sliderLabelHeight);

    }

}
