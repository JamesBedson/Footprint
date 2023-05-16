/*
  ==============================================================================

    DistortionDSP.h
    Created: 16 May 2023 10:36:35am
    Author:  Marina Hernandez Salas

  ==============================================================================
*/

#pragma once
#include "AudioProcessingModule.h"
#include <JuceHeader.h>

class Distortion : AudioProcessingModule {
    
public:
    Distortion();
    ~Distortion() override;
    
    void prepare(double sampleRate, int samplesPerBlock) override;
    void processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer& midiMessages) override;

private:
    
};
