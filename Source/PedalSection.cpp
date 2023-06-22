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
    //processorPtr->apvts.addParameterListener(ProcessingConstants::Pedals::Identifiers::slot1Param, this);
    //processorPtr->apvts.addParameterListener(ProcessingConstants::Pedals::Identifiers::slot2Param, this);
    //processorPtr->apvts.addParameterListener(ProcessingConstants::Pedals::Identifiers::slot3Param, this);
    //processorPtr->apvts.addParameterListener(ProcessingConstants::Pedals::Identifiers::slot4Param, this);
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
    
    for (int slotIdx = 0; slotIdx < activeComponents.size(); slotIdx++) {
        auto* pedalChoice       = slotParameterVector[slotIdx];
        int pedalTypeID;
        if (slotIdx == 0) {
            pedalTypeID   = static_cast<int>(processorPtr->apvts.getRawParameterValue(ProcessingConstants::Pedals::Identifiers::slot1Param)->load());
        }
        
        else if (slotIdx == 1) {
            pedalTypeID   = static_cast<int>(processorPtr->apvts.getRawParameterValue(ProcessingConstants::Pedals::Identifiers::slot2Param)->load());
        }
        
        else if (slotIdx == 2) {
            pedalTypeID = static_cast<int>(processorPtr->apvts.getRawParameterValue(ProcessingConstants::Pedals::Identifiers::slot3Param)->load());
        }
        
        else {
            pedalTypeID = static_cast<int>(processorPtr->apvts.getRawParameterValue(ProcessingConstants::Pedals::Identifiers::slot4Param)->load());
        }
        
        
        if (pedalTypeID == 0) {
            activeComponents[slotIdx] = createComboBox();
            activeComponents[slotIdx]->setMouseCursor(juce::MouseCursor::StandardCursorType::PointingHandCursor);
            addAndMakeVisible(*activeComponents[slotIdx]);
        }
        
        else if (pedalTypeID == 1) { // Compressor
            //this->removeChildComponent(activeComponents[slotIdx].get());
            activeComponents[slotIdx] = std::make_unique<CompressorPedal>(this->processorPtr, getCompressorParameterIDs(slotIdx), slotIdx + 1);
            auto* pedal = dynamic_cast<CompressorPedal*>(activeComponents[slotIdx].get());
            addAndMakeVisible(pedal);
            pedal->setBounds(*pedalSlots[slotIdx]);
            *pedalChoice = 1.f;
        }
        
        else if (pedalTypeID == 2) { // Distortion
            //this->removeChildComponent(activeComponents[slotIdx].get());
            activeComponents[slotIdx] = std::make_unique<DistortionPedal>(this->processorPtr, getDistortionParameterIDs(slotIdx), slotIdx + 1);
            auto* pedal = dynamic_cast<DistortionPedal*>(activeComponents[slotIdx].get());
            addAndMakeVisible(pedal);
            pedal->setBounds(*pedalSlots[slotIdx]);
            *pedalChoice = 2.f;
        }
        
        else if (pedalTypeID == 3) { // Envelope Filter
            //this->removeChildComponent(activeComponents[slotIdx].get());
            activeComponents[slotIdx] = std::make_unique<EnvelopePedal>(this->processorPtr, getEnvelopeFilterParameterIDs(slotIdx), slotIdx + 1);
            auto* pedal = dynamic_cast<EnvelopePedal*>(activeComponents[slotIdx].get());
            addAndMakeVisible(pedal);
            pedal->setBounds(*pedalSlots[slotIdx]);
            *pedalChoice = 3.f;
        }
        
        else if (pedalTypeID == 4) { // Reverb
            //this->removeChildComponent(activeComponents[slotIdx].get());
            activeComponents[slotIdx] = std::make_unique<ReverbPedal>(this->processorPtr, getReverbParameterIDs(slotIdx), slotIdx + 1);
            auto* pedal = dynamic_cast<ReverbPedal*>(activeComponents[slotIdx].get());
            addAndMakeVisible(pedal);
            pedal->setBounds(*pedalSlots[slotIdx]);
            *pedalChoice = 4.f;
        }
    }
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
    
    for (int i = 0 ; i < activeComponents.size(); i++) {
        auto& currentComponent = activeComponents.at(i);
        if (dynamic_cast<Pedal*>(currentComponent.get())) currentComponent->setBounds(*pedalSlots[i]);
        else currentComponent->setBounds(*boxSlots[i]);
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
    
    for (int slotIdx = 0; slotIdx < activeComponents.size(); slotIdx++) {
        auto& component     = activeComponents[slotIdx];
        auto* slotChoice    = slotParameterVector[slotIdx];
        
        if (auto* comboBox = dynamic_cast<juce::ComboBox*>(component.get())) {
            if (comboBox == comboBoxThatHasChanged) {
                auto pedalTypeID = comboBoxThatHasChanged->getSelectedId();
    
                if (pedalTypeID == 1) { // Compressor
                    this->removeChildComponent(activeComponents[slotIdx].get());
                    activeComponents[slotIdx] = std::make_unique<CompressorPedal>(this->processorPtr, getCompressorParameterIDs(slotIdx), slotIdx + 1);
                    auto* pedal = dynamic_cast<CompressorPedal*>(activeComponents[slotIdx].get());
                    addAndMakeVisible(pedal);
                    pedal->setBounds(*pedalSlots[slotIdx]);
                    *slotChoice = 1.f;
                }
                
                else if (pedalTypeID == 2) { // Distortion
                    this->removeChildComponent(activeComponents[slotIdx].get());
                    activeComponents[slotIdx] = std::make_unique<DistortionPedal>(this->processorPtr, getDistortionParameterIDs(slotIdx), slotIdx + 1);
                    auto* pedal = dynamic_cast<DistortionPedal*>(activeComponents[slotIdx].get());
                    addAndMakeVisible(pedal);
                    pedal->setBounds(*pedalSlots[slotIdx]);
                    *slotChoice = 2.f;
                }
                
                else if (pedalTypeID == 3) { // Envelope Filter
                    this->removeChildComponent(activeComponents[slotIdx].get());
                    activeComponents[slotIdx] = std::make_unique<EnvelopePedal>(this->processorPtr, getEnvelopeFilterParameterIDs(slotIdx), slotIdx + 1);
                    auto* pedal = dynamic_cast<EnvelopePedal*>(activeComponents[slotIdx].get());
                    addAndMakeVisible(pedal);
                    pedal->setBounds(*pedalSlots[slotIdx]);
                    *slotChoice = 3.f;
                }
                
                else if (pedalTypeID == 4) { // Reverb
                    this->removeChildComponent(activeComponents[slotIdx].get());
                    activeComponents[slotIdx] = std::make_unique<ReverbPedal>(this->processorPtr, getReverbParameterIDs(slotIdx), slotIdx + 1);
                    auto* pedal = dynamic_cast<ReverbPedal*>(activeComponents[slotIdx].get());
                    addAndMakeVisible(pedal);
                    pedal->setBounds(*pedalSlots[slotIdx]);
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
                ProcessingConstants::Compressor::Identifiers::compressorAttackID1,
                ProcessingConstants::Compressor::Identifiers::compressorReleaseID1,
                ProcessingConstants::Compressor::Identifiers::compressorThresholdID1,
                ProcessingConstants::Compressor::Identifiers::compressorRatioID1
            };
            
        case 1:
            return {
                ProcessingConstants::Compressor::Identifiers::compressorAttackID2,
                ProcessingConstants::Compressor::Identifiers::compressorReleaseID2,
                ProcessingConstants::Compressor::Identifiers::compressorThresholdID2,
                ProcessingConstants::Compressor::Identifiers::compressorRatioID2
            };
            
        case 2:
            return {
                ProcessingConstants::Compressor::Identifiers::compressorAttackID3,
                ProcessingConstants::Compressor::Identifiers::compressorReleaseID3,
                ProcessingConstants::Compressor::Identifiers::compressorThresholdID3,
                ProcessingConstants::Compressor::Identifiers::compressorRatioID3
            };
            
        case 3:
            return {
                ProcessingConstants::Compressor::Identifiers::compressorAttackID4,
                ProcessingConstants::Compressor::Identifiers::compressorReleaseID4,
                ProcessingConstants::Compressor::Identifiers::compressorThresholdID4,
                ProcessingConstants::Compressor::Identifiers::compressorRatioID4
            };
    }
    return {};
}

juce::StringArray PedalSection::getReverbParameterIDs(const int &idx){
    
    switch (idx) {
            
        case 0:
            return {
                ProcessingConstants::Reverb::Identifiers::reverbWetMixID1,
                ProcessingConstants::Reverb::Identifiers::reverbIRChoiceID1
            };
            
        case 1:
            return {
                ProcessingConstants::Reverb::Identifiers::reverbWetMixID2,
                ProcessingConstants::Reverb::Identifiers::reverbIRChoiceID2
            };
            
        case 2:
            return {
                ProcessingConstants::Reverb::Identifiers::reverbWetMixID3,
                ProcessingConstants::Reverb::Identifiers::reverbIRChoiceID3
            };
            
        case 3:
            return {
                ProcessingConstants::Reverb::Identifiers::reverbWetMixID4,
                ProcessingConstants::Reverb::Identifiers::reverbIRChoiceID4
            };
    }
    return {};
}

juce::StringArray PedalSection::getDistortionParameterIDs(const int &idx){
    
    switch (idx) {
            
        case 0:
            return {
                ProcessingConstants::Distortion::Identifiers::distortionGainID1,
                ProcessingConstants::Distortion::Identifiers::distortionLevelID1,
                ProcessingConstants::Distortion::Identifiers::distortionToneID1
            };
            
        case 1:
            return {
                ProcessingConstants::Distortion::Identifiers::distortionGainID2,
                ProcessingConstants::Distortion::Identifiers::distortionLevelID2,
                ProcessingConstants::Distortion::Identifiers::distortionToneID2
            };
            
        case 2:
            return {
                ProcessingConstants::Distortion::Identifiers::distortionGainID3,
                ProcessingConstants::Distortion::Identifiers::distortionLevelID3,
                ProcessingConstants::Distortion::Identifiers::distortionToneID3
            };
            
        case 3:
            return {
                ProcessingConstants::Distortion::Identifiers::distortionGainID4,
                ProcessingConstants::Distortion::Identifiers::distortionLevelID4,
                ProcessingConstants::Distortion::Identifiers::distortionToneID4
            };
    }
    return {};
    
}

juce::StringArray PedalSection::getEnvelopeFilterParameterIDs(const int &idx){
    
    switch (idx) {
            
        case 0:
            return {
                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterQualityID1,
                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterSensitivityID1,
                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterCutoffThresholdID1
            };
            
        case 1:
            return {
                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterQualityID2,
                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterSensitivityID2,
                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterCutoffThresholdID2
            };
            
        case 2:
            return {
                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterQualityID3,
                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterSensitivityID3,
                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterCutoffThresholdID3
            };
            
        case 3:
            return {
                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterQualityID4,
                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterSensitivityID4,
                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterCutoffThresholdID4
            };
    }
    return {};
}

void PedalSection::assignSlotChoice(const int &slotIdx, const int &pedalTypeID){
    
    auto* slotChoice    = slotParameterVector[slotIdx];
    if (pedalTypeID == 0) {
        
        activeComponents[slotIdx] = createComboBox();
        activeComponents[slotIdx]->setMouseCursor(juce::MouseCursor::StandardCursorType::PointingHandCursor);
        addAndMakeVisible(*activeComponents[slotIdx]);
        
    }
    
    else if (pedalTypeID == 1) { // Compressor
        this->removeChildComponent(activeComponents[slotIdx].get());
        activeComponents[slotIdx] = std::make_unique<CompressorPedal>(this->processorPtr, getCompressorParameterIDs(slotIdx), slotIdx + 1);
        auto* pedal = dynamic_cast<CompressorPedal*>(activeComponents[slotIdx].get());
        addAndMakeVisible(pedal);
        pedal->setBounds(*pedalSlots[slotIdx]);
        *slotChoice = 1.f;
    }
    
    else if (pedalTypeID == 2) { // Distortion
        this->removeChildComponent(activeComponents[slotIdx].get());
        activeComponents[slotIdx] = std::make_unique<DistortionPedal>(this->processorPtr, getDistortionParameterIDs(slotIdx), slotIdx + 1);
        auto* pedal = dynamic_cast<DistortionPedal*>(activeComponents[slotIdx].get());
        addAndMakeVisible(pedal);
        pedal->setBounds(*pedalSlots[slotIdx]);
        *slotChoice = 2.f;
    }
    
    else if (pedalTypeID == 3) { // Envelope Filter
        this->removeChildComponent(activeComponents[slotIdx].get());
        activeComponents[slotIdx] = std::make_unique<EnvelopePedal>(this->processorPtr, getEnvelopeFilterParameterIDs(slotIdx), slotIdx + 1);
        auto* pedal = dynamic_cast<EnvelopePedal*>(activeComponents[slotIdx].get());
        addAndMakeVisible(pedal);
        pedal->setBounds(*pedalSlots[slotIdx]);
        *slotChoice = 3.f;
    }
    
    else if (pedalTypeID == 4) { // Reverb
        this->removeChildComponent(activeComponents[slotIdx].get());
        activeComponents[slotIdx] = std::make_unique<ReverbPedal>(this->processorPtr, getReverbParameterIDs(slotIdx), slotIdx + 1);
        auto* pedal = dynamic_cast<ReverbPedal*>(activeComponents[slotIdx].get());
        addAndMakeVisible(pedal);
        pedal->setBounds(*pedalSlots[slotIdx]);
        *slotChoice = 4.f;
    }
    
}


