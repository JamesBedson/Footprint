/*
  ==============================================================================

    PedalSection.h
    Created: 6 May 2023 2:06:57pm
    Author:  James Bedson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Pedal.h"
#include "CompressorPedal.h"
#include "ReverbPedal.h"
#include "EnvelopePedal.h"
#include "DistortionPedal.h"
#include "PluginProcessor.h"
#include "ProcessingConstants.h"
#include "ComboBoxLookandFeel.h"


//==============================================================================
/*
*/

using ComponentVector = std::vector<std::unique_ptr<juce::Component>>;

class PedalSection  : public juce::Component, public juce::ComboBox::Listener, public juce::Timer
{
public:
    PedalSection(FootprintAudioProcessor* p);
    ~PedalSection() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;
    void timerCallback() override;

    ComboBoxLookandFeel comboBoxLookandFeel;

private:
    
    FootprintAudioProcessor* processorPtr;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PedalSection)
    
    juce::Rectangle<int> pedalSlot1, pedalSlot2, pedalSlot3, pedalSlot4;
    juce::Rectangle<int> boxSlot1, boxSlot2, boxSlot3, boxSlot4;
    
    std::vector<juce::Rectangle<int>*> pedalSlots   {&pedalSlot1, &pedalSlot2, &pedalSlot3, &pedalSlot4};
    std::vector<juce::Rectangle<int>*> boxSlots     {&boxSlot1, &boxSlot2, &boxSlot3, &boxSlot4};
    
    juce::AudioParameterChoice* slot1Choice;
    juce::AudioParameterChoice* slot2Choice;
    juce::AudioParameterChoice* slot3Choice;
    juce::AudioParameterChoice* slot4Choice;
    
    std::vector<juce::AudioParameterChoice*> slotParameterVector;
    
    juce::StringArray getCompressorParameterIDs(const int& idx);
    juce::StringArray getEnvelopeFilterParameterIDs(const int& idx);
    juce::StringArray getReverbParameterIDs(const int& idx);
    juce::StringArray getDistortionParameterIDs(const int& idx);
    
    ComponentVector activeComponents;
    
    void paintDecor(juce::Graphics&);

    std::unique_ptr<juce::ComboBox> createComboBox();
    
    juce::ComboBox      addPedal;
    
    /*
    CompressorPedal     compressorPedal;
    ReverbPedal         reverbPedal;
    EnvelopePedal       envelopePedal;
    DistortionPedal     distortionPedal;*/
};
