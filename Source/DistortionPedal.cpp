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
DistortionPedal::DistortionPedal(FootprintAudioProcessor* processor, juce::StringArray parameterIDs, const int& pedalSlot)
: Pedal(pedalSlot),
gainAttachment(processor->apvts, parameterIDs[0], gain),
levelAttachment(processor->apvts, parameterIDs[1], level),
toneAttachment(processor->apvts, parameterIDs[2], tone)
{
    p = processor;
    
    if          (pedalSlot == 1) bypassState.referTo(p->apvts.getParameterAsValue(ProcessingConstants::Distortion::Identifiers::distortionBypassedID1));
    else if     (pedalSlot == 2) bypassState.referTo(p->apvts.getParameterAsValue(ProcessingConstants::Distortion::Identifiers::distortionBypassedID2));
    else if     (pedalSlot == 3) bypassState.referTo(p->apvts.getParameterAsValue(ProcessingConstants::Distortion::Identifiers::distortionBypassedID3));
    else if     (pedalSlot == 4) bypassState.referTo(p->apvts.getParameterAsValue(ProcessingConstants::Distortion::Identifiers::distortionBypassedID4));
    else jassertfalse;
    
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
    labelFont.setHeight(GUIAttributes::PedalFontSizes::h2);    gainLabel.setFont(labelFont);
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
    
    if (pedalSlot == 1){
        g.drawImage(backgroundSlot1, getLocalBounds().toFloat(), juce::RectanglePlacement::stretchToFit);
    } else if (pedalSlot == 2){
        g.drawImage(backgroundSlot2, getLocalBounds().toFloat(), juce::RectanglePlacement::stretchToFit);
    } else if (pedalSlot == 3){
        g.drawImage(backgroundSlot3, getLocalBounds().toFloat(), juce::RectanglePlacement::stretchToFit);
    } else if (pedalSlot == 4){
        g.drawImage(backgroundSlot4, getLocalBounds().toFloat(), juce::RectanglePlacement::stretchToFit);
    } else {
        return;
    }
}
