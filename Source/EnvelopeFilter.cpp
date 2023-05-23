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

    window.resize(numChannels);
    for (int ch = 0; ch < numChannels; ch++) { window[ch].resize(0); }


}

void EnvelopeFilter::processBlock(juce::AudioBuffer<float>& buffer,
    juce::MidiBuffer& midiMessages) {

    juce::AudioBuffer<float> ampBuffer = getAmplitudeEnvelope(buffer);
    double currentCutoff = 0.0;
    double averageCutoffFreq = 0.0;
    Matrix coefficients;
    std::vector<float> previousX;
    float xN, xN1, xN2, yN1, yN2;

    for (int ch = 0; ch < buffer.getNumChannels(); ch++) {

        auto* channelDataWrite = buffer.getWritePointer(ch);
        //auto* channelDataRead = buffer.getReadPointer(ch);
        auto* envelopeDataRead = ampBuffer.getReadPointer(ch);

        for (int n = 0; n < buffer.getNumSamples(); n++) {
            
            currentCutoff = thresholdMinFreq + sensitivity->get() * envelopeDataRead[n] * (sampleRate / 2 - thresholdMinFreq);
            window[ch].push_back(currentCutoff);

            if (window[ch].size() > windowSize) { window[ch].erase(window[ch].begin()); }
            for (double value : window[ch])
                averageCutoffFreq += value;
            averageCutoffFreq /= window[ch].size();

            coefficients = getLPFCoefficients(averageCutoffFreq, qualityFactor->get());

            if (n == 0 || n == 1) {
                previousX = { channelDataWrite[0], channelDataWrite[1] };
            }
            else {

                /*xN = chann
                xN1 = buffer.getSample(ch, n - 1);
                xN2 = buffer.getSample(ch, n - 2);

                yN1 = envelopeBuffer.getSample(ch, n - 1);
                yN2 = envelopeBuffer.getSample(ch, n - 2);

                y = ba[0][0] * xN + ba[0][1] * xN1 + ba[0][2] * xN2 - ba[1][1] * yN1 - ba[1][2] * yN2;
                envelopeBuffer.setSample(ch, n, y);*/
            }

        }
        averageCutoffFreq = 0.0;
    }


}

Matrix EnvelopeFilter::getLPFCoefficients(double cutoffFreq, float qualityFactor) {

    double w              = 2.0 * juce::MathConstants<double>::pi * cutoffFreq / sampleRate;
    double alpha          = std::sin(w) / (2.0 * qualityFactor);

    double b0             = (1.0 - std::cos(w)) / 2.0;
    double b1             = 1.0 - std::cos(w);
    double b2             = b0;
    double a0             = 1.0 + alpha;
    double a1             = -2.0 * std::cos(w);
    double a2             = 1.0 - alpha;

    Matrix ba = { { b0, b1, b2 }, { a0, a1, a2 } };

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

    Matrix ba = getLPFCoefficients(cutoff1, 1.0f); // qualityFactor = 1

    return applyLPF(ampBuffer, ba);
}

juce::AudioBuffer<float> EnvelopeFilter::applyLPF(juce::AudioBuffer<float> buffer, Matrix ba) {

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




void EnvelopeFilter::setQualityFactor(juce::Atomic<float>* q) {
    if (q >= 0) { this->qualityFactor = q; }
}

void EnvelopeFilter::setSensitivity(juce::Atomic<float>* s) {
    if (s >= 0) { this->sensitivity = s; }
}

void EnvelopeFilter::setSampleRate(double s) {
    if (s > 0) { sampleRate = s; }
}

void EnvelopeFilter::setCutoff(double c) {
    if (c > 0) { cutoff1 = c; }
}

void EnvelopeFilter::setThresholdMinFreq(double t) {
    if (t > 0) { thresholdMinFreq = t; }
}

//void EnvelopeFilter::setNyquist() {
//    nyquist = sampleRate / 2;
//}

void EnvelopeFilter::setWindowSize(int w) {
    if (w > 0) { windowSize = w; }
}