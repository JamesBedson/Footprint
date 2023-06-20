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
    this->windowSize = 400;

    windowCutoffs.resize(numChannels);
    previousXamplitude.resize(numChannels);
    previousYamplitude.resize(numChannels);
    previousXsignal.resize(numChannels);
    previousYsignal.resize(numChannels);

    for (int ch = 0; ch < numChannels; ch++) {

        windowCutoffs[ch].resize(windowSize);
        previousXamplitude[ch].resize(2);
        previousYamplitude[ch].resize(2);
        previousXsignal[ch].resize(2);
        previousYsignal[ch].resize(2);

        for (int n = 0; n < windowSize; n++) windowCutoffs[ch][n] = 0.0;
        for (int n : {0, 1}) {
            previousXamplitude[ch][n] = 0.f;
            previousYamplitude[ch][n] = 0.f;
            previousXsignal[ch][n] = 0.f;
            previousYsignal[ch][n] = 0.f;
        }
    }
}

void EnvelopeFilter::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) {
    if (this->isBypassed()) return;
    
    juce::AudioBuffer<float> ampBuffer = getAmplitudeEnvelope(buffer);

    double currentCutoff, amplitude, averageCutoffFreq, minCutoff, sens, Q, nyquist;

    averageCutoffFreq = 0.0;
    minCutoff = static_cast<double>(minCutoffFrequency->load());
    sens = static_cast<double>(sensitivity->load());
    Q = static_cast<double>(qualityFactor->load());
    nyquist = static_cast<double>(sampleRate) / 2.0;

    for (int ch = 0; ch < buffer.getNumChannels(); ch++) {

        auto* envelopeDataRead = ampBuffer.getReadPointer(ch);

        for (int n = 0; n < buffer.getNumSamples(); n++) {
            
            amplitude = static_cast<double>(envelopeDataRead[n]);
            currentCutoff = minCutoff + sens * amplitude * (nyquist - minCutoff);
            std::rotate(windowCutoffs[ch].begin(), windowCutoffs[ch].begin() + 1, windowCutoffs[ch].end());
            windowCutoffs[ch][windowSize - 1] = currentCutoff;

            for (double value : windowCutoffs[ch]) averageCutoffFreq += value;
            averageCutoffFreq /= windowSize;

            applyLPF(buffer, ch, n, averageCutoffFreq, Q, previousXsignal, previousYsignal);

            averageCutoffFreq = 0.0;
        }
    }
}

DMatrix EnvelopeFilter::getLPFCoefficients(double cutoffFreq, double qualityFactor) {

    double w, alpha, b0, b1, b2, a0, a1, a2;
    
    w          = 2.0 * juce::MathConstants<double>::pi * cutoffFreq / sampleRate;
    alpha      = std::sin(w) / (2.0 * qualityFactor);

    b0         = (1.0 - std::cos(w)) / 2.0;
    b1         = 1.0 - std::cos(w);
    b2         = b0;
    a0         = 1.0 + alpha;
    a1         = -2.0 * std::cos(w);
    a2         = 1.0 - alpha;

    DMatrix ba = { { b0 / a0, b1 / a0, b2 / a0 }, { a1 / a0, a2 / a0 } }; // with normalisation

    return ba;
}

void EnvelopeFilter::applyLPF(juce::AudioBuffer<float>& buffer, int ch, int n, double cutoff, double qFactor, FMatrix& previousX, FMatrix& previousY) {
    
    auto* channelDataWrite = buffer.getWritePointer(ch);
    auto* channelDataRead = buffer.getReadPointer(ch);
    
    float xN1, xN2, yN1, yN2, b0, b1, b2, a1, a2;

    DMatrix coefficients = getLPFCoefficients(cutoff, qFactor);

    xN1 = previousX[ch][0];
    xN2 = previousX[ch][1];
    yN1 = previousY[ch][0];
    yN2 = previousY[ch][1];
    b0 = static_cast<float>(coefficients[0][0]);
    b1 = static_cast<float>(coefficients[0][1]);
    b2 = static_cast<float>(coefficients[0][2]);
    a1 = static_cast<float>(coefficients[1][0]);
    a2 = static_cast<float>(coefficients[1][1]);

    previousX[ch][0] = previousX[ch][1];
    previousX[ch][1] = channelDataRead[n];

    channelDataWrite[n] = b0 * channelDataRead[n] + b1 * xN2 + b2 * xN1 - a1 * yN2 - a2 * yN1;

    previousY[ch][0] = previousY[ch][1];
    previousY[ch][1] = channelDataRead[n];
}

juce::AudioBuffer<float> EnvelopeFilter::getAmplitudeEnvelope(const juce::AudioBuffer<float>& buffer) {

    juce::AudioBuffer<float> ampBuffer;
    ampBuffer.makeCopyOf(buffer);

    for (int ch = 0; ch < buffer.getNumChannels(); ch++) {

        auto* channelDataWrite = ampBuffer.getWritePointer(ch);
        auto* channelDataRead = ampBuffer.getReadPointer(ch);
        for (int n = 0; n < buffer.getNumSamples(); n++) {
            channelDataWrite[n] = std::abs(channelDataRead[n]);
            applyLPF(ampBuffer, ch, n, 1000.0, 1.0, previousXamplitude, previousYamplitude);
        }
    }

    return ampBuffer;
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
