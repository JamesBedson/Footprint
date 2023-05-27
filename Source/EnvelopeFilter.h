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
    void applyLPF(juce::AudioBuffer<float>& buffer, int ch, int n, double cutoff, double qFactor, FMatrix& previousX, FMatrix& previousY);

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
    FMatrix previousXamplitude;
    FMatrix previousYamplitude;
    FMatrix previousXsignal;
    FMatrix previousYsignal;
    bool isFirst;

};
