/*
  ==============================================================================

    ARAverager.h
    Created: 21 May 2023 7:34:51pm
    Author:  James Bedson

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "AudioProcessingModule.h"
#define MIN_TIME_CONST 0.000001

class ARAverager : public AudioProcessingModule{
    
public:
    
    ARAverager();
    ~ARAverager() override;
    
    void prepare(double sampleRate, int samplesPerBlock, int numChannels) override;
    void processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer& midiMessages) override;
    
    void setAttack(juce::Atomic<float>* attack);
    void setRelease(juce::Atomic<float>* release);
    
private:
    juce::Atomic<float>*    attack;
    juce::Atomic<float>*    release;
    
    double                  alphaA, alphaR;
    double                  sampleRate;
    std::vector<float>      previousOuts;
    
    
};
