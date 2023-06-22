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
ReverbPedal::ReverbPedal(FootprintAudioProcessor* processor, juce::StringArray parameterIDs, const int& pedalSlot)
: Pedal(pedalSlot),
mixAttachment(processor->apvts, parameterIDs[0], mix),
reverbTypeSwitch(processor, parameterIDs[1].toStdString())
{
    p = processor;
    
    if          (pedalSlot == 1) {
        bypassState.referTo(p->apvts.getParameterAsValue(ProcessingConstants::Reverb::Identifiers::reverbBypassedID1));
        irSetting.referTo(p->apvts.getParameterAsValue(ProcessingConstants::Reverb::Identifiers::reverbIRChoiceID1));
    }
    
    else if     (pedalSlot == 2) {
        bypassState.referTo(p->apvts.getParameterAsValue(ProcessingConstants::Reverb::Identifiers::reverbBypassedID2));
        irSetting.referTo(p->apvts.getParameterAsValue(ProcessingConstants::Reverb::Identifiers::reverbIRChoiceID2));
    }
    
    else if     (pedalSlot == 3) {
        bypassState.referTo(p->apvts.getParameterAsValue(ProcessingConstants::Reverb::Identifiers::reverbBypassedID3));
        irSetting.referTo(p->apvts.getParameterAsValue(ProcessingConstants::Reverb::Identifiers::reverbIRChoiceID3));
    }
    
    else if     (pedalSlot == 4) {
        bypassState.referTo(p->apvts.getParameterAsValue(ProcessingConstants::Reverb::Identifiers::reverbBypassedID4));
        irSetting.referTo(p->apvts.getParameterAsValue(ProcessingConstants::Reverb::Identifiers::reverbIRChoiceID4));
    }
    else jassertfalse;
    
    for (auto& slider : sliders){
        slider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        slider->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0,0);
        slider->setLookAndFeel(&pedalLookAndFeel);
    }
    addAndMakeVisible(mix);
    for (auto& label : sliderLabels) {
        addAndMakeVisible(label);
        label->setJustificationType(juce::Justification::horizontallyCentred);
    }
    addAndMakeVisible(reverbTypeSwitch);
    startTimerHz(30);

    mixLabel.attachToComponent(&mix, false);
    typeLabel.attachToComponent(&reverbTypeSwitch, false);

    juce::Font labelFont;
    labelFont.setTypefaceName("Futura");
    labelFont.setHeight(GUIAttributes::PedalFontSizes::h2);
    mixLabel.setFont(labelFont);
    typeLabel.setFont(labelFont);

    mixLabel.setText("Mix", juce::dontSendNotification);

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
    
    for (auto& slider : sliders) {
        slider->setSize(sliderWidth, sliderHeight);
        }
    mix.setCentrePosition                       (sliderCol2CentreX, sliderRow2CentreY - 85);
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
    juce::Rectangle<int> switchBounds(switchX, switchY - 80, switchWidth, switchHeight + 80);
    reverbTypeSwitch.setBounds(switchBounds);
}

void ReverbPedal::paintBackground(juce::Graphics& g){
    
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

void ReverbPedal::timerCallback() {
    
    if (reverbTypeSwitch.currentSettingChanged){
        
        float choice;
        
        if (pedalSlot == 1)
            choice = p->apvts.getRawParameterValue(ProcessingConstants::Reverb::Identifiers::reverbIRChoiceID1)->load();
        
        else if (pedalSlot == 2)
            choice = p->apvts.getRawParameterValue(ProcessingConstants::Reverb::Identifiers::reverbIRChoiceID2)->load();
        
        else if (pedalSlot == 3)
            choice = p->apvts.getRawParameterValue(ProcessingConstants::Reverb::Identifiers::reverbIRChoiceID3)->load();
        
        else if (pedalSlot == 4)
            choice = p->apvts.getRawParameterValue(ProcessingConstants::Reverb::Identifiers::reverbIRChoiceID4)->load();
        
        else return;
        
        irSetting = static_cast<int>(choice + 1) % 4;
        reverbTypeSwitch.currentSettingChanged = false;
        
    }
    
}
