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
ReverbPedal::ReverbPedal(FootprintAudioProcessor* processor, juce::StringArray parameterIDs)
: mixAttachment(processor->apvts, parameterIDs[0], mix),
lowpassAttachment(processor->apvts, parameterIDs[1], lowCut),
highpassAttachment(processor->apvts, parameterIDs[2], highCut)
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
    addAndMakeVisible(reverbTypeSwitch);
    //type.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    //type.setRange(0, 3, 1); // Range from 0 to 3 with a step size of 1
    //type.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0); // Hide the text box
    //type.setNumDecimalPlacesToDisplay(0); // Display integers only
    //type.setPopupDisplayEnabled(true, false, this); // Enable the popup display
    //type.setColour(juce::Slider::backgroundColourId, juce::Colours::white.withAlpha(0.5f));
    //type.setColour(juce::Slider::trackColourId, juce::Colours::lightblue);
    //type.setColour(juce::Slider::thumbColourId, juce::Colours::white);


    mixLabel.attachToComponent(&mix, false);
    highCutLabel.attachToComponent(&highCut, false);
    lowCutLabel.attachToComponent(&lowCut, false);
    typeLabel.attachToComponent(&reverbTypeSwitch, false);

    juce::Font labelFont;
    labelFont.setTypefaceName("Futura");
    labelFont.setHeight(GUIAttributes::PedalFontSizes::h2);
    mixLabel.setFont(labelFont);
    highCutLabel.setFont(labelFont);
    lowCutLabel.setFont(labelFont);
    typeLabel.setFont(labelFont);

    mixLabel.setText("Mix", juce::dontSendNotification);
    highCutLabel.setText("H.Cut", juce::dontSendNotification);
    lowCutLabel.setText("L.Cut", juce::dontSendNotification);;
    //typeLabel.setText("Type", juce::dontSendNotification);
}

ReverbPedal::~ReverbPedal()
{
    for (auto* slider : sliders){
        slider->setLookAndFeel(nullptr);
    }
}

void ReverbPedal::paintAdditionalComponents(juce::Graphics& g)
{
    juce::Rectangle<int> textBounds = getLocalBounds().withY(getHeight() * -0.38f);

    juce::Font font;
    font.setTypefaceName("Futura");
    font.setHeight(GUIAttributes::PedalFontSizes::h1);
    g.setFont(font); // Set the updated font

    g.drawText ("REVERB", textBounds,
                juce::Justification::centred, true);   // draw some placeholder text
}

void ReverbPedal::paint(juce::Graphics& g)
{
    Pedal::paint(g); // Call the base class paint function
    paintAdditionalComponents(g);
}

void ReverbPedal::resizeChild(){
    
    //for (auto& slider : sliders){
    //    if (slider != &reverbTypeSwitch){
    //        slider->setSize(sliderWidth, sliderHeight);
    //    }
    //    else type.setSize(150, 50);
    //}
    for (auto& slider : sliders) {
        slider->setSize(sliderWidth, sliderHeight);
        }
    mix.setCentrePosition                       (sliderCol2CentreX, sliderRow2CentreY - 20);
    highCut.setCentrePosition                   (sliderCol3CentreX, sliderRow1CentreY);
    lowCut.setCentrePosition                    (sliderCol1CentreX, sliderRow1CentreY);
    reverbTypeSwitch.setCentrePosition          (sliderCol2CentreX, sliderRow3CentreY);

    for (auto& label : sliderLabels) {

        auto sliderBounds   = label->getAttachedComponent()->getBounds();
        auto bottomX        = sliderBounds.getBottomLeft().getX();
        auto bottomY        = sliderBounds.getBottomLeft().getY();

        label->setBounds(bottomX, bottomY, sliderLabelWidth, sliderLabelHeight);
    }
    int switchWidth = 140;
    int switchHeight = 20;
    int switchX = sliderCol2CentreX - switchWidth / 2;
    int switchY = sliderRow3CentreY - switchHeight / 2 - 10;
    juce::Rectangle<int> switchBounds(switchX, switchY, switchWidth, switchHeight);
    reverbTypeSwitch.setBounds(switchBounds);
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
}