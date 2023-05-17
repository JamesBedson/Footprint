/*
  ==============================================================================

    Envelope.cpp
    Created: 15 May 2023 6:54:58pm
    Author:  bmarc

  ==============================================================================
*/

#include "EnvelopeFilter.h"


EnvelopeFilter::EnvelopeFilter() {
}

EnvelopeFilter::~EnvelopeFilter() {

}

void EnvelopeFilter::prepare(double sampleRate, int samplePerBlock) {

}

void EnvelopeFilter::processBlock(juce::AudioBuffer<float>& buffer,
    juce::MidiBuffer& midiMessages, double sampleRate) {

    juce::AudioBuffer<float> ampBuffer = getAmplitudeEnvelope(buffer);




}

Matrix EnvelopeFilter::getLPFCoefficients() {

    double w              = 2.0 * juce::MathConstants<double>::pi * cutoff1 / sampleRate;
    double alpha          = std::sin(w) / (2.0 * qualityFactor);

    double b0             = (1.0 - std::cos(w)) / 2.0;
    double b1             = 1.0 - std::cos(w);
    double b2             = b0;
    double a0             = 1.0 + alpha;
    double a1             = -2.0 * std::cos(w);
    double a2             = 1.0 - alpha;

    std::vector<double> b = { b0, b1, b2 };
    std::vector<double> a = { a0, a1, a2 };

    Matrix ba = { b,a };

    // Normalisation:
    for (int i = 0; i < ba.size(); i++) { for (int j = 0; j < ba[0].size(); j++) { ba[i][j] /= a0; } }

    return ba;
}

juce::AudioBuffer<float> EnvelopeFilter::getAmplitudeEnvelope(const juce::AudioBuffer<float>& buffer) {

    juce::AudioBuffer<float> ampBuffer;
    ampBuffer.makeCopyOf(buffer);

    for (int i = 0; i < ampBuffer.getNumSamples(); i++) {
        for (int j = 0; j < ampBuffer.getNumChannels(); j++) { ampBuffer.setSample(j, i, std::abs(ampBuffer.getSample(j, i))); }
    }

    Matrix ba = getLPFCoefficients();

    return applyLPF(ampBuffer, ba);
}

juce::AudioBuffer<float> EnvelopeFilter::applyLPF(juce::AudioBuffer<float> buffer, Matrix ba) {

    juce::AudioBuffer<float> envelopeBuffer;
    envelopeBuffer.makeCopyOf(buffer);

    float xN, xN1, xN2, yN1, yN2, y;

    for (int i = 0; i < envelopeBuffer.getNumSamples(); i++) {
        for (int j = 0; j < envelopeBuffer.getNumChannels(); j++) {
            if (i == 0 || i == 1) { envelopeBuffer.setSample(j, i, 0.0); }
            else {

                xN  = buffer.getSample(j, i);
                xN1 = buffer.getSample(j, i - 1);
                xN2 = buffer.getSample(j, i - 2);

                yN1 = envelopeBuffer.getSample(j, i - 1);
                yN2 = envelopeBuffer.getSample(j, i - 2);

                y   = ba[0][0] * xN + ba[0][1] * xN1 + ba[0][2] * xN2 - ba[1][1] * yN1 - ba[1][2] * yN2;
                envelopeBuffer.setSample(j, i, y);
            }
        }
    }

    return envelopeBuffer;
}