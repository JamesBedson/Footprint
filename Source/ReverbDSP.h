/*
  ==============================================================================

    ReverbDSP.h
    Created: 17 May 2023 5:35:08pm
    Author:  Pau Segalés Torres

  ==============================================================================
*/

#pragma once
#include "AudioProcessingModule.h"
#include <JuceHeader.h>

class Reverb : AudioProcessingModule {
    
public:
    Reverb();
    ~Reverb() override;
    
    void prepare(double sampleRate, int samplesPerBlock) override;
    void processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer& midiMessages) override;

private:


    
};
