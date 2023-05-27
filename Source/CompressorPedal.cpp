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
CompressorPedal::CompressorPedal(FootprintAudioProcessor* processor, juce::StringArray parameterIDs)
: attackAttachment(processor->apvts, parameterIDs[0], attack),
releaseAttachment(processor->apvts, parameterIDs[1], release),
thresholdAttachment(processor->apvts, parameterIDs[2], threshold),
ratioAttachment(processor->apvts, parameterIDs[3], ratio)
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


    juce::Font labelFont;

    labelFont.setTypefaceName("Futura");
    labelFont.setHeight(GUIAttributes::PedalFontSizes::h2);
    thresholdLabel.setFont(labelFont);
    ratioLabel.setFont(labelFont);
    attackLabel.setFont(labelFont);
    releaseLabel.setFont(labelFont);
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
    juce::Rectangle<int> textBounds = getLocalBounds().withY(getHeight() * -0.38f);

    juce::Font font;
    font.setHeight(GUIAttributes::PedalFontSizes::h1);
    font.setTypefaceName("Futura");
    g.setFont(font);

    g.drawText("COMPRESSOR",
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
}
