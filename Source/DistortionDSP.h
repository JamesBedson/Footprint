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

using FMatrix = std::vector<std::vector<float>>;

class Distortion : public AudioProcessingModule {
    
public:
    Distortion();
    ~Distortion() override;
    
    void prepare(double sampleRate, int samplesPerBlock, int numChannels) override;
    void processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer& midiMessages) override;

    FMatrix getLPFCoefficients(float cutoffFreq);
    void applyLPF(juce::AudioBuffer<float>& buffer, int ch, int n, double cutoff, FMatrix& previousX, FMatrix& previousY);
    
    FMatrix getBPFCoefficients(float cutoffFreq);
    void applyBPF(juce::AudioBuffer<float>& buffer, int ch, int n, double cutoff, FMatrix& previousX, FMatrix& previousY);

    float dsp(const float* ori, int num_samples);

    void setGain(std::atomic<float>*);
    void setLevel(std::atomic<float>*);
    void setTone(std::atomic<float>*);
    
    
private:
    
    std::atomic<float>* gain;
    std::atomic<float>* level;
    std::atomic<float>* tone;

    double sampleRate;
    FMatrix previousXsignal;
    FMatrix previousYsignal;
    
};
