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
    isFirst = false;

    window.resize(numChannels);
    for (int ch = 0; ch < numChannels; ch++) {
        window[ch].resize(windowSize);
        for (int n = 0; n < windowSize; n++)
            window[ch][n] = 0.0;
    }

}

void EnvelopeFilter::processBlock(juce::AudioBuffer<float>& buffer,
    juce::MidiBuffer& midiMessages) {

    juce::AudioBuffer<float> ampBuffer = getAmplitudeEnvelope(buffer);
    double currentCutoff;
    double averageCutoffFreq = 0.0;
    Matrix coefficients;
    std::vector<float> previousX;
    float xN, xN1, xN2, yN1, yN2;
    int times = 1;

    for (int ch = 0; ch < buffer.getNumChannels(); ch++) {

        auto* channelDataWrite = buffer.getWritePointer(ch);
        //auto* channelDataRead = buffer.getReadPointer(ch);
        auto* envelopeDataRead = ampBuffer.getReadPointer(ch);

        for (int n = 0; n < buffer.getNumSamples(); n++) {
            

            currentCutoff = static_cast<double>(minCutoffFrequency->load()) + static_cast<double>(sensitivity->load()) * envelopeDataRead[n] * (sampleRate / 2 - static_cast<double>(minCutoffFrequency->load()));
            std::rotate(window[ch].begin(), window[ch].begin() + 1, window[ch].end());
            window[ch][windowSize - 1] = currentCutoff;

            for (double value : window[ch]) averageCutoffFreq += value;


            if (!isFirst) {
                averageCutoffFreq /= times;
                times += 1;
            }
            else { averageCutoffFreq /= windowSize;}

            coefficients = getLPFCoefficients(averageCutoffFreq, static_cast<double>(qualityFactor->load()));


            if (n == 0 || n == 1) {
                previousX = { channelDataWrite[0], channelDataWrite[1] }; //CANVI?
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
            averageCutoffFreq = 0.0;
        }
    }
    if (!isFirst) isFirst = true;
}

Matrix EnvelopeFilter::getLPFCoefficients(double cutoffFreq, double qualityFactor) {

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

    Matrix ba = getLPFCoefficients(static_cast<double>(minCutoffFrequency->load()), 1.0); // qualityFactor = 1

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


void EnvelopeFilter::setQualityFactor(std::atomic<float>* q) {
    if (q->load() >= 0.f) { this->qualityFactor = q; }
}

void EnvelopeFilter::setSensitivity(std::atomic<float>* s) {
    if (s->load() >= 0) { this->sensitivity = s; }
}

void EnvelopeFilter::setMinCutoffFreq(std::atomic<float>* m) {
    if (m->load() >= 0) { this->minCutoffFrequency = m; }
}

//void EnvelopeFilter::setSampleRate(double s) {
//    if (s > 0) { sampleRate = s; }
//}

//void EnvelopeFilter::setCutoff(double c) {
//    if (c > 0) { cutoff1 = c; }
//}

//void EnvelopeFilter::setThresholdMinFreq(double t) {
//    if (t > 0) { thresholdMinFreq = t; }
//}

//void EnvelopeFilter::setNyquist() {
//    nyquist = sampleRate / 2;
//}

//void EnvelopeFilter::setWindowSize(int w) {
//    if (w > 0) { windowSize = w; }
//}

