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

    void prepare(double sampleRate, int samplePerBlock) override;
    void processBlock(juce::AudioBuffer<float>& buffer,
        juce::MidiBuffer& midiMessages) override;

    void setSampleRate(double s) {
        if (s > 0) { sampleRate = s; }
    }

    void setQualityFactor(float q) {
        if (q >= 0) { qualityFactor = q; }
    }

    void setSensitivity(float s) {
        if (s >= 0) { sensitivity = s; }
    }

    void setCutoff1(double c) {
        if (c > 0) { cutoff1 = c; }
    }

    void setThresholdMinFreq(double t) {
        if (t > 0) { thresholdMinFreq = t; }
    }

    void setNyquist() {
        nyquist = sampleRate / 2;
    }

    void setWindowSize(int w) {
        if (w > 0) { windowSize = w; }
    }

    //void setWindow() {
    //for (int i = 0; i < windowSize; i++) { window[i] = 0.0; }
    //}

    Matrix getLPFCoefficients();
    juce::AudioBuffer<float> getAmplitudeEnvelope(const juce::AudioBuffer<float>& buffer);
    juce::AudioBuffer<float> applyLPF(juce::AudioBuffer<float> buffer, Matrix ba);

private:

    double sampleRate;
    float qualityFactor;
    float sensitivity;


    double cutoff1;
    double thresholdMinFreq;
    double nyquist;
    int windowSize;
    //std::vector<double>& window;

};