/*
  ==============================================================================

    DistortionDSP.cpp
    Created: 16 May 2023 10:36:35am
    Author:  Marina Hernandez Salas

  ==============================================================================
*/

#include "DistortionDSP.h"

Distortion::Distortion(){
    
}

Distortion::~Distortion(){
    
}

void Distortion::prepare(double sampleRate, int samplesPerBlock, int numChannels){
    this->sampleRate = sampleRate;

    previousXsignal.resize(numChannels);
    previousYsignal.resize(numChannels);

    for (int ch = 0; ch < numChannels; ch++) {

        previousXsignal[ch].resize(2);
        previousYsignal[ch].resize(2);
        for (int n : {0, 1}) {
            previousXsignal[ch][n] = 0.f;
            previousYsignal[ch][n] = 0.f;
        }
    }
}

void Distortion::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages){
    if (this->isBypassed()) return;
    
    float value, nyquist, cutoff, toneVal, gainVal, waveShaper, levelVal, sign;

    gainVal = gain->load();
    toneVal = tone->load();
    levelVal = level->load();

    nyquist = sampleRate / 2;
    cutoff = nyquist * toneVal;
    

    for (int ch = 0; ch < buffer.getNumChannels(); ch++) {
        auto* channelDataWrite = buffer.getWritePointer(ch);
        auto* channelDataRead = buffer.getReadPointer(ch);

        for (int n = 0; n < buffer.getNumSamples(); n++) {
            
            // Tone:            
            if (toneVal < 0.5f) applyFilter(true, buffer, ch, n, cutoff, previousXsignal, previousYsignal); // Low pass filter
            else if (toneVal > 0.65f) applyFilter(false, buffer, ch, n, 500.f * toneVal * toneVal, previousXsignal, previousYsignal); // High pass filter

            // Gain:
            value = channelDataRead[n];

            waveShaper = 1.f - std::exp(-gainVal * std::abs(value));
            if (value >= 0.f) sign = 1.f;
            else            sign = -1.f;

            channelDataWrite[n] = sign * waveShaper;

            // Level:
            channelDataWrite[n] *= levelVal;
        }
    }
}

FMatrix Distortion::getLPFCoefficients(float cutoffFreq) {

    float w, alpha, b0, b1, b2, a0, a1, a2;

    w          = 2.f * juce::MathConstants<float>::pi * cutoffFreq / this->sampleRate;
    alpha      = std::sin(w) / (2.f * 1.f); // Q = 1

    b0         = (1.f - std::cos(w)) / 2.f;
    b1         = 1.f - std::cos(w);
    b2         = b0;
    a0         = 1.f + alpha;
    a1         = - 2.f * std::cos(w);
    a2         = 1.f - alpha;

    FMatrix ba = { { b0 / a0, b1 / a0, b2 / a0 }, { a1 / a0, a2 / a0 } }; // with normalisation

    return ba;
}

FMatrix Distortion::getHPFCoefficients(float cutoffFreq) {

    float w, Q, alpha, b0, b1, b2, a0, a1, a2;
    
    w          = 2.f * juce::MathConstants<float>::pi * cutoffFreq / this->sampleRate;
    Q          = 5.f;
    alpha      = std::sin(w) / (2.f * Q);

    b0         = (1.f + std::cos(w)) / 2.f;
    b1         = - 1.f - std::cos(w);
    b2         = (1.f + std::cos(w)) / 2.f;
    a0         = 1.f + alpha;
    a1         = - 2.f * std::cos(w);
    a2         = 1.f - alpha;

    FMatrix ba = { { b0 / a0, b1 / a0, b2 / a0 }, { a1 / a0, a2 / a0 } }; // with normalisation

    return ba;
}

void Distortion::applyFilter(bool type, juce::AudioBuffer<float>& buffer, int ch, int n, double cutoff, FMatrix& previousX, FMatrix& previousY) {

    auto* channelDataWrite = buffer.getWritePointer(ch);
    auto* channelDataRead = buffer.getReadPointer(ch);

    float xN1, xN2, yN1, yN2, b0, b1, b2, a1, a2;

    FMatrix coefficients;

    if (type) coefficients = getLPFCoefficients(cutoff);
    else coefficients = getHPFCoefficients(cutoff);

    xN1 = previousX[ch][0];
    xN2 = previousX[ch][1];
    yN1 = previousY[ch][0];
    yN2 = previousY[ch][1];
    b0  = coefficients[0][0];
    b1  = coefficients[0][1];
    b2  = coefficients[0][2];
    a1  = coefficients[1][0];
    a2  = coefficients[1][1];

    previousX[ch][0] = previousX[ch][1];
    previousX[ch][1] = channelDataRead[n];

    channelDataWrite[n] = b0 * channelDataRead[n] + b1 * xN2 + b2 * xN1 - a1 * yN2 - a2 * yN1;

    previousY[ch][0] = previousY[ch][1];
    previousY[ch][1] = channelDataRead[n];
}

void Distortion::setGain(std::atomic<float>* gain){
    this->gain = gain;
}

void Distortion::setLevel(std::atomic<float>* level){
    this->level = level;
}

void Distortion::setTone(std::atomic<float> *tone){
    this->tone = tone;
}
