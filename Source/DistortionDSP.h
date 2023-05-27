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

class Distortion : public AudioProcessingModule {
    
public:
    Distortion();
    ~Distortion() override;
    
    void prepare(double sampleRate, int samplesPerBlock, int numChannels) override;
    void processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer& midiMessages) override;

    void setGain(std::atomic<float>*);
    void setLevel(std::atomic<float>*);
    void setTone(std::atomic<float>*);
    
    
private:
    
    std::atomic<float>* gain;
    std::atomic<float>* level;
    std::atomic<float>* tone;
    
};
