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
PedalSection::PedalSection(FootprintAudioProcessor* processor)
{
    processorPtr = processor;
    processorPtr->apvts.addParameterListener(ProcessingConstants::Pedals::Identifiers::slot1Param, this);
    processorPtr->apvts.addParameterListener(ProcessingConstants::Pedals::Identifiers::slot2Param, this);
    processorPtr->apvts.addParameterListener(ProcessingConstants::Pedals::Identifiers::slot3Param, this);
    processorPtr->apvts.addParameterListener(ProcessingConstants::Pedals::Identifiers::slot4Param, this);
    activeComponents.resize(4);
    slotParameterVector.resize(4);
    
    for (int componentIdx = 0; componentIdx < activeComponents.size(); componentIdx++){
        activeComponents[componentIdx] = createComboBox();
        activeComponents[componentIdx]->setMouseCursor(juce::MouseCursor::StandardCursorType::PointingHandCursor);
        addAndMakeVisible(activeComponents[componentIdx].get());
    }
    startTimerHz(25);
    
    slot1Choice = static_cast<juce::AudioParameterChoice*>(processor->apvts.getParameter(ProcessingConstants::Pedals::Identifiers::slot1Param));
    slot2Choice = static_cast<juce::AudioParameterChoice*>(processor->apvts.getParameter(ProcessingConstants::Pedals::Identifiers::slot2Param));
    slot3Choice = static_cast<juce::AudioParameterChoice*>(processor->apvts.getParameter(ProcessingConstants::Pedals::Identifiers::slot3Param));
    slot4Choice = static_cast<juce::AudioParameterChoice*>(processor->apvts.getParameter(ProcessingConstants::Pedals::Identifiers::slot4Param));

    slotParameterVector[0] = slot1Choice;
    slotParameterVector[1] = slot2Choice;
    slotParameterVector[2] = slot3Choice;
    slotParameterVector[3] = slot4Choice;
    
}

PedalSection::~PedalSection()
{
}

void PedalSection::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::white);   
    paintDecor(g);
}

void PedalSection::resized()
{
    juce::Rectangle<int> bounds = getLocalBounds();
    
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
    
    boxSlot1.setSize(slotSizeWidth, slotSizeHeight * 0.1f);
    boxSlot1.setCentre(slot1Centre);
    
    boxSlot2.setSize(slotSizeWidth, slotSizeHeight * 0.1f);
    boxSlot2.setCentre(slot2Centre);
    
    boxSlot3.setSize(slotSizeWidth, slotSizeHeight * 0.1f);
    boxSlot3.setCentre(slot3Centre);
    
    boxSlot4.setSize(slotSizeWidth, slotSizeHeight * 0.1f);
    boxSlot4.setCentre(slot4Centre);
    
    for (int componentIdx = 0; componentIdx < activeComponents.size(); componentIdx++){
        activeComponents[componentIdx]->setBounds(*boxSlots[componentIdx]);
    }
    
}

void PedalSection::paintDecor(juce::Graphics& g) {

    juce::Line<float> line1(juce::Point<float>((getLocalBounds().getWidth() * 0.25f) - 17.0f, getLocalBounds().getHeight() * 0.5f), juce::Point<float>((getLocalBounds().getWidth() * 0.25f) + 20.0f, getLocalBounds().getHeight() * 0.5f));
    juce::Line<float> line2(juce::Point<float>((getLocalBounds().getWidth() * 0.5f) - 17.0f, getLocalBounds().getHeight() * 0.5f), juce::Point<float>((getLocalBounds().getWidth() * 0.5f) + 20.0f, getLocalBounds().getHeight() * 0.5f));
    juce::Line<float> line3(juce::Point<float>((getLocalBounds().getWidth() * 0.75f) - 17.0f, getLocalBounds().getHeight() * 0.5f), juce::Point<float>((getLocalBounds().getWidth() * 0.75f) + 20.0f, getLocalBounds().getHeight() * 0.5f));
    juce::Line<float> line4(juce::Point<float>((getLocalBounds().getWidth()) - 17.0f, getLocalBounds().getHeight() * 0.5f), juce::Point<float>((getLocalBounds().getWidth()) + 50.0f, getLocalBounds().getHeight() * 0.5f));
    juce::Line<float> line5(juce::Point<float>((getLocalBounds().getWidth() * (-1.0f)), getLocalBounds().getHeight() * 0.5f), juce::Point<float>((getLocalBounds().getWidth() * 0.02f), getLocalBounds().getHeight() * 0.5f));


    g.drawLine(line1, 2.0f);
    g.drawLine(line2, 2.0f);
    g.drawLine(line3, 2.0f);
    g.drawLine(line4, 2.0f);
    g.drawLine(line5, 2.0f);

}

std::unique_ptr<juce::ComboBox> PedalSection::createComboBox(){
   
    auto newComboBox = std::make_unique<juce::ComboBox>();
    
    addAndMakeVisible(newComboBox.get());
    newComboBox->setMouseCursor(juce::MouseCursor::StandardCursorType::PointingHandCursor);
    newComboBox->setLookAndFeel(&comboBoxLookandFeel);
    newComboBox->setJustificationType(juce::Justification::centred);
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
        auto& component     = activeComponents[componentIdx];
        auto* slotChoice    = slotParameterVector[componentIdx];
        
        if (auto* pedal = dynamic_cast<Pedal*>(component.get())) {
            if (pedal->isDeleted()) {
                activeComponents[componentIdx] = createComboBox();
                activeComponents[componentIdx]->setBounds(*boxSlots[componentIdx]);
                *slotChoice = 0;
            }
        }
    }
}

void PedalSection::comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged) {
    for (int componentIdx = 0; componentIdx < activeComponents.size(); componentIdx++) {
        auto& component     = activeComponents[componentIdx];
        auto* slotChoice    = slotParameterVector[componentIdx];
        
        if (auto* comboBox = dynamic_cast<juce::ComboBox*>(component.get())) {
            if (comboBox == comboBoxThatHasChanged) {
                
                auto optionSelected = comboBoxThatHasChanged->getSelectedId();

                if (optionSelected == 1) { // Compressor
                    this->removeChildComponent(comboBox);
                    activeComponents[componentIdx] = std::make_unique<CompressorPedal>(this->processorPtr, getCompressorParameterIDs(componentIdx), componentIdx + 1);
                    auto* pedal = dynamic_cast<CompressorPedal*>(activeComponents[componentIdx].get());
                    addAndMakeVisible(pedal);
                    pedal->setBounds(*pedalSlots[componentIdx]);
                    *slotChoice = 1.f;
                }
                
                else if (optionSelected == 2) { // Distortion
                    this->removeChildComponent(comboBox);
                    activeComponents[componentIdx] = std::make_unique<DistortionPedal>(this->processorPtr, getDistortionParameterIDs(componentIdx), componentIdx + 1);
                    auto* pedal = dynamic_cast<DistortionPedal*>(activeComponents[componentIdx].get());
                    addAndMakeVisible(pedal);
                    pedal->setBounds(*pedalSlots[componentIdx]);
                    *slotChoice = 2.f;
                }
                
                else if (optionSelected == 3) { // Envelope Filter
                    this->removeChildComponent(comboBox);
                    activeComponents[componentIdx] = std::make_unique<EnvelopePedal>(this->processorPtr, getEnvelopeFilterParameterIDs(componentIdx), componentIdx + 1);
                    auto* pedal = dynamic_cast<EnvelopePedal*>(activeComponents[componentIdx].get());
                    addAndMakeVisible(pedal);
                    pedal->setBounds(*pedalSlots[componentIdx]);
                    *slotChoice = 3.f;
                }
                
                else if (optionSelected == 4) { // Reverb
                    this->removeChildComponent(comboBox);
                    activeComponents[componentIdx] = std::make_unique<ReverbPedal>(this->processorPtr, getReverbParameterIDs(componentIdx), componentIdx + 1);
                    auto* pedal = dynamic_cast<ReverbPedal*>(activeComponents[componentIdx].get());
                    addAndMakeVisible(pedal);
                    pedal->setBounds(*pedalSlots[componentIdx]);
                    *slotChoice = 4.f;
                }
            }
        }
    }
}

juce::StringArray PedalSection::getCompressorParameterIDs(const int &idx){
    
    switch (idx) {
            
        case 0:
            return {
                ProcessingConstants::Compressor::Identifiers::compressorAttack1,
                ProcessingConstants::Compressor::Identifiers::compressorRelease1,
                ProcessingConstants::Compressor::Identifiers::compressorThreshold1,
                ProcessingConstants::Compressor::Identifiers::compressorRatio1
            };
            
        case 1:
            return {
                ProcessingConstants::Compressor::Identifiers::compressorAttack2,
                ProcessingConstants::Compressor::Identifiers::compressorRelease2,
                ProcessingConstants::Compressor::Identifiers::compressorThreshold2,
                ProcessingConstants::Compressor::Identifiers::compressorRatio2
            };
            
        case 2:
            return {
                ProcessingConstants::Compressor::Identifiers::compressorAttack3,
                ProcessingConstants::Compressor::Identifiers::compressorRelease3,
                ProcessingConstants::Compressor::Identifiers::compressorThreshold3,
                ProcessingConstants::Compressor::Identifiers::compressorRatio3
            };
            
        case 3:
            return {
                ProcessingConstants::Compressor::Identifiers::compressorAttack4,
                ProcessingConstants::Compressor::Identifiers::compressorRelease4,
                ProcessingConstants::Compressor::Identifiers::compressorThreshold4,
                ProcessingConstants::Compressor::Identifiers::compressorRatio4
            };
    }
    return {};
}

juce::StringArray PedalSection::getReverbParameterIDs(const int &idx){
    
    switch (idx) {
            
        case 0:
            return {
                ProcessingConstants::Reverb::Identifiers::reverbWetMix1,
                ProcessingConstants::Reverb::Identifiers::reverbCutoffLowpass1,
                ProcessingConstants::Reverb::Identifiers::reverbCutoffHighpass1,
                ProcessingConstants::Reverb::Identifiers::reverbIRChoice1
            };
            
        case 1:
            return {
                ProcessingConstants::Reverb::Identifiers::reverbWetMix2,
                ProcessingConstants::Reverb::Identifiers::reverbCutoffLowpass2,
                ProcessingConstants::Reverb::Identifiers::reverbCutoffHighpass2,
                ProcessingConstants::Reverb::Identifiers::reverbIRChoice2
            };
            
        case 2:
            return {
                ProcessingConstants::Reverb::Identifiers::reverbWetMix3,
                ProcessingConstants::Reverb::Identifiers::reverbCutoffLowpass3,
                ProcessingConstants::Reverb::Identifiers::reverbCutoffHighpass3,
                ProcessingConstants::Reverb::Identifiers::reverbIRChoice3
            };
            
        case 3:
            return {
                ProcessingConstants::Reverb::Identifiers::reverbWetMix4,
                ProcessingConstants::Reverb::Identifiers::reverbCutoffLowpass4,
                ProcessingConstants::Reverb::Identifiers::reverbCutoffHighpass4,
                ProcessingConstants::Reverb::Identifiers::reverbIRChoice4
            };
    }
    return {};
}

juce::StringArray PedalSection::getDistortionParameterIDs(const int &idx){
    
    switch (idx) {
            
        case 0:
            return {
                ProcessingConstants::Distortion::Identifiers::distortionGain1,
                ProcessingConstants::Distortion::Identifiers::distortionLevel1,
                ProcessingConstants::Distortion::Identifiers::distortionTone1
            };
            
        case 1:
            return {
                ProcessingConstants::Distortion::Identifiers::distortionGain2,
                ProcessingConstants::Distortion::Identifiers::distortionLevel2,
                ProcessingConstants::Distortion::Identifiers::distortionTone2
            };
            
        case 2:
            return {
                ProcessingConstants::Distortion::Identifiers::distortionGain3,
                ProcessingConstants::Distortion::Identifiers::distortionLevel3,
                ProcessingConstants::Distortion::Identifiers::distortionTone3
            };
            
        case 3:
            return {
                ProcessingConstants::Distortion::Identifiers::distortionGain4,
                ProcessingConstants::Distortion::Identifiers::distortionLevel4,
                ProcessingConstants::Distortion::Identifiers::distortionTone4
            };
    }
    return {};
    
}

juce::StringArray PedalSection::getEnvelopeFilterParameterIDs(const int &idx){
    
    switch (idx) {
            
        case 0:
            return {
                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterQuality1,
                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterSensitivity1,
                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterCutoffThreshold1
            };
            
        case 1:
            return {
                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterQuality2,
                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterSensitivity2,
                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterCutoffThreshold2
            };
            
        case 2:
            return {
                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterQuality3,
                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterSensitivity3,
                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterCutoffThreshold3
            };
            
        case 3:
            return {
                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterQuality4,
                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterSensitivity4,
                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterCutoffThreshold4
            };
    }
    return {};
}

void PedalSection::parameterChanged (const juce::String& parameterID, float newValue) {
    
}
