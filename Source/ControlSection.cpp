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

    juce::Font font;
    font.setHeight(GUIAttributes::ControlFontSizes::h2);
    font.setTypefaceName("Futura");
    inputLabel.setFont(font);
    outputLabel.setFont(font);

    inputLabel.setText("Input", juce::dontSendNotification);
    outputLabel.setText("Output", juce::dontSendNotification);
}

ControlSection::~ControlSection()
{
    for (auto* slider : sliders){
        slider->setLookAndFeel(nullptr);
    }
}

void ControlSection::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::white);
    paintDecor(g);
}

void ControlSection::resized()
{
    auto bounds       = getBounds();
    auto width        = getWidth();
    auto height       = getHeight();
    sliderCol1CentreX = getX() + width * 0.25f;
    sliderRow1CentreY = getY() + height * 0.45f;
    sliderCol2CentreX = getX() + width * 0.71f;
    sliderRow2CentreY = getY() + height * 0.72f;

    sliderWidth       = 75;
    sliderHeight      = 75;

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
void ControlSection::paintDecor(juce::Graphics &g){
    
    juce::Line<float> line1 (juce::Point<float>((getLocalBounds().getWidth() * (-1.0f)), getLocalBounds().getHeight() * 0.45f), juce::Point<float>((getLocalBounds().getWidth() * (0.07f)), getLocalBounds().getHeight() * 0.45f));
    /*juce::Line<float> line2(juce::Point<float>((getLocalBounds().getWidth() * 0.5f) - 17.0f, getLocalBounds().getHeight() * 0.5f), juce::Point<float>((getLocalBounds().getWidth() * 0.5f) + 20.0f, getLocalBounds().getHeight() * 0.5f));
    juce::Line<float> line3(juce::Point<float>((getLocalBounds().getWidth() * 0.75f) - 17.0f, getLocalBounds().getHeight() * 0.5f), juce::Point<float>((getLocalBounds().getWidth() * 0.75f) + 20.0f, getLocalBounds().getHeight() * 0.5f));*/
    
    
    g.drawLine(line1, 2.0f);
    /*g.drawLine(line2, 2.0f);
    g.drawLine(line3, 2.0f);*/

    
}
