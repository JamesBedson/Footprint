/*
  ==============================================================================

    PassThrough.h
    Created: 6 Jun 2023 10:47:39pm
    Author:  James Bedson

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "AudioProcessingModule.h"

class AudioPassThrough : public AudioProcessingModule {
private:
    
public:
    
    void prepare(double sampleRate, int samplesPerBlock, int numChannels) override {
        
    };
    
    void processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer& midiMessages) override {
        
    };
};
