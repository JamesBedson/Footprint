/*
  ==============================================================================

    PedalSection.cpp
    Created: 6 May 2023 2:06:57pm
    Author:  James Bedson

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PedalSection.h"

//==============================================================================
PedalSection::PedalSection()
{
    activeComponents.resize(4);
    
    for (int componentIdx = 0; componentIdx < activeComponents.size(); componentIdx++){
        activeComponents[componentIdx] = createComboBox();
        addAndMakeVisible(activeComponents[componentIdx].get());
    }
    startTimerHz(25);
    /*
    addAndMakeVisible(compressorPedal);
    addAndMakeVisible(reverbPedal);
    addAndMakeVisible(envelopePedal);
    addAndMakeVisible(distortionPedal);*/

}

PedalSection::~PedalSection()
{
}

void PedalSection::paint (juce::Graphics& g)
{
    //g.setColour (juce::Colours::white.darker().darker());
    //g.drawRoundedRectangle(getLocalBounds().toFloat(), 15.0f, 1.0f);
    //g.setColour(juce::Colours::transparentBlack);
    ////g.fillRoundedRectangle(getLocalBounds().toFloat(), 15.0f);
    //g.setFont (14.0f);
    g.setColour(juce::Colours::white);
    
    //paintDecor(g);
    

}

void PedalSection::resized()
{
    juce::Rectangle<int> bounds = getLocalBounds();
    
    /*
    compressorPedal.setSlot(1);
    distortionPedal.setSlot(2);
    reverbPedal.setSlot(3);
    envelopePedal.setSlot(4);*/
    
    int slotSizeWidth   = 200;
    int slotSizeHeight  = 300;
    
    juce::Point<int> slot1Centre(bounds.getX() + getWidth() * 0.25f - slotSizeWidth * 0.58f, bounds.getCentreY());
    juce::Point<int> slot2Centre(bounds.getX() + getWidth() * 0.5f - slotSizeWidth * 0.58f, bounds.getCentreY());
    juce::Point<int> slot3Centre(bounds.getX() + getWidth() * 0.75f - slotSizeWidth * 0.58f, bounds.getCentreY());
    juce::Point<int> slot4Centre(bounds.getX() + getWidth() - slotSizeWidth * 0.58f, bounds.getCentreY());
    
    pedalSlot1.setSize(slotSizeWidth, slotSizeHeight);
    pedalSlot1.setCentre(slot1Centre);
    
    pedalSlot2.setSize(slotSizeWidth, slotSizeHeight);
    pedalSlot2.setCentre(slot2Centre);
    
    pedalSlot3.setSize(slotSizeWidth, slotSizeHeight);
    pedalSlot3.setCentre(slot3Centre);
    
    pedalSlot4.setSize(slotSizeWidth, slotSizeHeight);
    pedalSlot4.setCentre(slot4Centre);
    
    boxSlot1.setSize(slotSizeWidth, slotSizeHeight * 0.5f);
    boxSlot1.setCentre(slot1Centre);
    
    boxSlot2.setSize(slotSizeWidth, slotSizeHeight * 0.5f);
    boxSlot2.setCentre(slot2Centre);
    
    boxSlot3.setSize(slotSizeWidth, slotSizeHeight * 0.5f);
    boxSlot3.setCentre(slot3Centre);
    
    boxSlot4.setSize(slotSizeWidth, slotSizeHeight * 0.5f);
    boxSlot4.setCentre(slot4Centre);
    
    for (int componentIdx = 0; componentIdx < activeComponents.size(); componentIdx++){
        activeComponents[componentIdx]->setBounds(*boxSlots[componentIdx]);
    }
    
    /*
    compressorPedal.setBounds(pedalSlot4);
    envelopePedal.setBounds(pedalSlot1);
    reverbPedal.setBounds(pedalSlot3);
    distortionPedal.setBounds(pedalSlot2);*/
}

void PedalSection::paintDecor(juce::Graphics &g){
    
    juce::Line<float> line1 (juce::Point<float>((getLocalBounds().getWidth() * 0.25f) - 17.0f, getLocalBounds().getHeight() * 0.5f), juce::Point<float>((getLocalBounds().getWidth() * 0.25f) + 20.0f, getLocalBounds().getHeight() * 0.5f));
    juce::Line<float> line2(juce::Point<float>((getLocalBounds().getWidth() * 0.5f) - 17.0f, getLocalBounds().getHeight() * 0.5f), juce::Point<float>((getLocalBounds().getWidth() * 0.5f) + 20.0f, getLocalBounds().getHeight() * 0.5f));
    juce::Line<float> line3(juce::Point<float>((getLocalBounds().getWidth() * 0.75f) - 17.0f, getLocalBounds().getHeight() * 0.5f), juce::Point<float>((getLocalBounds().getWidth() * 0.75f) + 20.0f, getLocalBounds().getHeight() * 0.5f));
    juce::Line<float> line4(juce::Point<float>((getLocalBounds().getWidth()) - 17.0f, getLocalBounds().getHeight() * 0.5f), juce::Point<float>((getLocalBounds().getWidth()) + 50.0f, getLocalBounds().getHeight() * 0.5f));
    
    g.drawLine(line1, 2.0f);
    g.drawLine(line2, 2.0f);
    g.drawLine(line3, 2.0f);
    g.drawLine(line4, 2.0f);
    
}

std::unique_ptr<juce::ComboBox> PedalSection::createComboBox(){
   
    auto newComboBox = std::make_unique<juce::ComboBox>();
    addAndMakeVisible(newComboBox.get());
    newComboBox->setText("Add Pedal");
    newComboBox->addItem("Compressor", 1);
    newComboBox->addItem("Distortion", 2);
    newComboBox->addItem("Envelope Filter", 3);
    newComboBox->addItem("Reverb", 4);
    newComboBox->addListener(this);
    
    return newComboBox;
}

void PedalSection::timerCallback() {
    for (int componentIdx = 0; componentIdx < activeComponents.size(); componentIdx++) {
        auto& component = activeComponents[componentIdx];
        
        if (auto* pedal = dynamic_cast<Pedal*>(component.get())) {
            if (pedal->isDeleted()) {
                activeComponents[componentIdx] = createComboBox();
                activeComponents[componentIdx]->setBounds(*boxSlots[componentIdx]);
            }
        }
    }
}

void PedalSection::comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged) {
    for (int componentIdx = 0; componentIdx < activeComponents.size(); componentIdx++) {
        auto& component = activeComponents[componentIdx];

        if (auto* comboBox = dynamic_cast<juce::ComboBox*>(component.get())) {
            if (comboBox == comboBoxThatHasChanged) {
                
                auto optionSelected = comboBoxThatHasChanged->getSelectedId();

                if (optionSelected == 1) { // Compressor
                    this->removeChildComponent(comboBox);
                    activeComponents[componentIdx] = std::make_unique<CompressorPedal>();
                    auto* pedal = dynamic_cast<CompressorPedal*>(activeComponents[componentIdx].get());
                    addAndMakeVisible(pedal);
                    pedal->setSlot(componentIdx + 1);
                    pedal->setBounds(*pedalSlots[componentIdx]);
                    
                }
                else if (optionSelected == 2) { // Distortion
                    this->removeChildComponent(comboBox);
                    activeComponents[componentIdx] = std::make_unique<DistortionPedal>();
                    auto* pedal = dynamic_cast<DistortionPedal*>(activeComponents[componentIdx].get());
                    addAndMakeVisible(pedal);
                    pedal->setSlot(componentIdx + 1);
                    pedal->setBounds(*pedalSlots[componentIdx]);
                }
                else if (optionSelected == 3) { // Envelope Filter
                    this->removeChildComponent(comboBox);
                    activeComponents[componentIdx] = std::make_unique<EnvelopePedal>();
                    auto* pedal = dynamic_cast<EnvelopePedal*>(activeComponents[componentIdx].get());
                    addAndMakeVisible(pedal);
                    pedal->setSlot(componentIdx + 1);
                    pedal->setBounds(*pedalSlots[componentIdx]);
                }
                else if (optionSelected == 4) { // Reverb
                    this->removeChildComponent(comboBox);
                    activeComponents[componentIdx] = std::make_unique<ReverbPedal>();
                    auto* pedal = dynamic_cast<ReverbPedal*>(activeComponents[componentIdx].get());
                    addAndMakeVisible(pedal);
                    pedal->setSlot(componentIdx + 1);
                    pedal->setBounds(*pedalSlots[componentIdx]);
                }
            }
        }
    }
}
