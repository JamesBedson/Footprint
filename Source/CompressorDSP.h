/*
  ==============================================================================

    CompressorDSP.h
    Created: 15 May 2023 6:48:31pm
    Author:  James Bedson

  ==============================================================================
*/

#pragma once
#include "AudioProcessingModule.h"
#include <JuceHeader.h>

class Compressor : AudioProcessingModule {
    
public:
    Compressor();
    ~Compressor() override;
    
    void prepare(double sampleRate, int samplesPerBlock) override;
    void processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer& midiMessages, double sampleRate) override;

private:
    
};



