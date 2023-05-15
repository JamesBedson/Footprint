/*
  ==============================================================================

    Envelope.h
    Created: 15 May 2023 6:54:58pm
    Author:  bmarc

  ==============================================================================
*/

#pragma once
<<<<<<< Updated upstream
=======
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

    void setQualityFactor(float q) {
        if (q >= 0) { qualityFactor = q; }
    }

    void setSensitivity(float s) {
        if (s >= 0) { sensitivity = s; }
    }


    Matrix getLPFCoefficients(double sampleRate, float cutoffFrequency, float qualityFactor);
    juce::AudioBuffer<float> getAmplitudeEnvelope(const juce::AudioBuffer<float>&buffer, double sampleRate);

private:
    float qualityFactor;
    float sensitivity;
};
>>>>>>> Stashed changes
