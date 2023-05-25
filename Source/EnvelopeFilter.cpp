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

void EnvelopeFilter::prepare(double sampleRate, int samplePerBlock, int numChannels) {

    this->sampleRate = sampleRate;
    isFirst = true;
    this->windowSize = 500;

    windowCutoffs.resize(numChannels);
    previousX.resize(numChannels);
    previousY.resize(numChannels);

    for (int ch = 0; ch < numChannels; ch++) {
        windowCutoffs[ch].resize(windowSize);
        previousX[ch].resize(2);
        previousY[ch].resize(2);

        for (int n = 0; n < windowSize; n++) windowCutoffs[ch][n] = 0.0;
        for (int n : {0, 1}) {
            previousX[ch][n] = 0.f;
            previousY[ch][n] = 0.f;
        }
    }
}

void EnvelopeFilter::processBlock(juce::AudioBuffer<float>& buffer,
    juce::MidiBuffer& midiMessages) {

    juce::AudioBuffer<float> ampBuffer = getAmplitudeEnvelope(buffer);
    double currentCutoff;
    double averageCutoffFreq = 0.0;
    int times = 1;
    double minCutoff = static_cast<double>(minCutoffFrequency->load());
    double sens = static_cast<double>(sensitivity->load());
    double amplitude;

    for (int ch = 0; ch < buffer.getNumChannels(); ch++) {

        auto* channelDataWrite = buffer.getWritePointer(ch);
        auto* channelDataRead = buffer.getReadPointer(ch);
        auto* envelopeDataRead = ampBuffer.getReadPointer(ch);

        for (int n = 0; n < buffer.getNumSamples(); n++) {
            
            amplitude = static_cast<double>(envelopeDataRead[n]);
            currentCutoff = minCutoff + sens * amplitude * (sampleRate / 2.0 - minCutoff);
            std::rotate(windowCutoffs[ch].begin(), windowCutoffs[ch].begin() + 1, windowCutoffs[ch].end());
            windowCutoffs[ch][windowSize - 1] = currentCutoff;

            for (double value : windowCutoffs[ch]) averageCutoffFreq += value;

            if (isFirst) {
                averageCutoffFreq /= times;
                times++;
            }
            else {
                averageCutoffFreq /= windowSize;
            }
            
            applyLPF(channelDataRead, channelDataWrite, ch, n, averageCutoffFreq);

            averageCutoffFreq = 0.0;
        }
    }
    if (isFirst) isFirst = false;
}

DMatrix EnvelopeFilter::getLPFCoefficients(double cutoffFreq, double qualityFactor) {

    double w              = 2.0 * juce::MathConstants<double>::pi * cutoffFreq / sampleRate;
    double alpha          = std::sin(w) / (2.0 * qualityFactor);

    double b0             = (1.0 - std::cos(w)) / 2.0;
    double b1             = 1.0 - std::cos(w);
    double b2             = b0;
    double a0             = 1.0 + alpha;
    double a1             = -2.0 * std::cos(w);
    double a2             = 1.0 - alpha;

    DMatrix ba = { { b0, b1, b2 }, { a0, a1, a2 } };

    // Normalisation:
    for (int i = 0; i < ba.size(); i++) { for (int j = 0; j < ba[0].size(); j++) { ba[i][j] /= a0; } }

    return ba;
}

juce::AudioBuffer<float> EnvelopeFilter::getAmplitudeEnvelope(const juce::AudioBuffer<float>& buffer) {

    juce::AudioBuffer<float> ampBuffer;
    ampBuffer.makeCopyOf(buffer);

    for (int ch = 0; ch < ampBuffer.getNumChannels(); ch++) {
        for (int n = 0; n < ampBuffer.getNumSamples(); n++) { ampBuffer.setSample(ch, n, std::abs(ampBuffer.getSample(ch, n))); }
    }

    DMatrix ba = getLPFCoefficients(1000.0, 1.0); // cutoff = 1000, qualityFactor = 1

    return applySimpleLPF(ampBuffer, ba);
}

juce::AudioBuffer<float> EnvelopeFilter::applySimpleLPF(juce::AudioBuffer<float> buffer, DMatrix ba) {

    juce::AudioBuffer<float> envelopeBuffer;
    envelopeBuffer.makeCopyOf(buffer);

    float xN, xN1, xN2, yN1, yN2, y;

    for (int ch = 0; ch < envelopeBuffer.getNumChannels(); ch++) {
        for (int n = 0; n < envelopeBuffer.getNumSamples(); n++) {
            if (n == 0 || n == 1) { envelopeBuffer.setSample(ch, n, 0.f); }
            else {

                xN  = buffer.getSample(ch, n);
                xN1 = buffer.getSample(ch, n - 1);
                xN2 = buffer.getSample(ch, n - 2);

                yN1 = envelopeBuffer.getSample(ch, n - 1);
                yN2 = envelopeBuffer.getSample(ch, n - 2);

                y   = ba[0][0] * xN + ba[0][1] * xN1 + ba[0][2] * xN2 - ba[1][1] * yN1 - ba[1][2] * yN2;
                envelopeBuffer.setSample(ch, n, y);
            }
        }
    }

    return envelopeBuffer;
}

void EnvelopeFilter::applyLPF(const float* read, float* write, int ch, int n, double cutoff) {
    float xN1, xN2, yN1, yN2, b0, b1, b2, a1, a2;

    DMatrix coefficients = getLPFCoefficients(cutoff, static_cast<double>(qualityFactor->load()));

    xN1 = previousX[ch][0];
    xN2 = previousX[ch][1];
    yN1 = previousY[ch][0];
    yN2 = previousY[ch][1];
    b0 = static_cast<float>(coefficients[0][0]);
    b1 = static_cast<float>(coefficients[0][1]);
    b2 = static_cast<float>(coefficients[0][2]);
    a1 = static_cast<float>(coefficients[1][1]);
    a2 = static_cast<float>(coefficients[1][2]);

    previousX[ch][0] = previousX[ch][1];
    previousX[ch][1] = read[n];

    write[n] = b0 * read[n] + b1 * xN2 + b2 * xN1 + a1 * yN2 + a2 * yN1;

    previousY[ch][0] = previousY[ch][1];
    previousY[ch][1] = read[n];
}


void EnvelopeFilter::setQualityFactor(std::atomic<float>* q) {
    if (q->load() >= 0.f) { this->qualityFactor = q; }
}

void EnvelopeFilter::setSensitivity(std::atomic<float>* s) {
    if (s->load() >= 0) { this->sensitivity = s; }
}

void EnvelopeFilter::setMinCutoffFreq(std::atomic<float>* m) {
    if (m->load() >= 0) { this->minCutoffFrequency = m; }
}