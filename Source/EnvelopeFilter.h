/*
  ==============================================================================

    Envelope.h
    Created: 15 May 2023 6:54:58pm
    Author:  bmarc

  ==============================================================================
*/


#pragma once
#include "AudioProcessingModule.h"
#include <JuceHeader.h>
using DMatrix = std::vector<std::vector<double>>;
using FMatrix = std::vector<std::vector<float>>;

class EnvelopeFilter : AudioProcessingModule {

public:
    EnvelopeFilter();
    ~EnvelopeFilter() override;

    void prepare(double sampleRate, int samplePerBlock, int numChannels) override;
    void processBlock(juce::AudioBuffer<float>& buffer,
        juce::MidiBuffer& midiMessages) override;

    DMatrix getLPFCoefficients(double cutoffFreq, double qFactor);
    juce::AudioBuffer<float> getAmplitudeEnvelope(const juce::AudioBuffer<float>& buffer);
    juce::AudioBuffer<float> applySimpleLPF(juce::AudioBuffer<float> buffer, DMatrix ba);
    void applyLPF(const float* read, float* write, int ch, int n, double cutoff);

    void setQualityFactor(std::atomic<float>* q);
    void setSensitivity(std::atomic<float>* s);
    void setMinCutoffFreq(std::atomic<float>* m);

private:
    
    std::atomic<float>* qualityFactor;
    std::atomic<float>* sensitivity;
    std::atomic<float>* minCutoffFrequency;

    double sampleRate;
    int windowSize;
    DMatrix windowCutoffs;
    FMatrix previousX;
    FMatrix previousY;
    bool isFirst;

};
