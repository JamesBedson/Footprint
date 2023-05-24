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
using Matrix = std::vector<std::vector<double>>;

class EnvelopeFilter : AudioProcessingModule {

public:
    EnvelopeFilter();
    ~EnvelopeFilter() override;

    void prepare(double sampleRate, int samplePerBlock, int numChannels) override;
    void processBlock(juce::AudioBuffer<float>& buffer,
        juce::MidiBuffer& midiMessages) override;

    Matrix getLPFCoefficients(double cutoffFreq, float qFactor);
    juce::AudioBuffer<float> getAmplitudeEnvelope(const juce::AudioBuffer<float>& buffer);
    juce::AudioBuffer<float> applyLPF(juce::AudioBuffer<float> buffer, Matrix ba);

    void setQualityFactor(std::atomic<float>* q);
    void setSensitivity(std::atomic<float>* s);
    void setMinCutoffFreq(std::atomic<float>* m);
    void setSampleRate(double s);
    void setCutoff(double c);
    void setThresholdMinFreq(double t);
    //void setNyquist(double n);
    void setWindowSize(int w);


private:
    
    std::atomic<float>* qualityFactor;
    std::atomic<float>* sensitivity;
    std::atomic<float>* minCutoffFrequency;

    double sampleRate;
    double cutoff1;
    double thresholdMinFreq;
    //double nyquist;
    int windowSize;
    Matrix window;

};
