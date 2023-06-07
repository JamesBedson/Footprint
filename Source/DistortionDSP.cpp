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
    
    float value, cutoff;

    for (int ch = 0; ch < buffer.getNumChannels(); ch++) {

        auto* channelDataWrite = buffer.getWritePointer(ch);
        auto* channelDataRead = buffer.getReadPointer(ch);

        for (int n = 0; n < buffer.getNumSamples(); n++) {
            
            // Tone:
            //cutoff = std::pow(10.f, (53.f - tone->load()) / 10.f);
            //cutoff = tone->load();
            //applyBPF(buffer, ch, n, cutoff, previousXsignal, previousYsignal);
            
            // Gain:
            if (gain->load() > 0.f) {
                value = channelDataRead[n];
                channelDataWrite[n] = (value / std::abs(value)) * (1 - std::exp(- gain->load() * std::abs(value)));
            }
            
        }
    }

}

FMatrix Distortion::getLPFCoefficients(float cutoffFreq) {

    float w = 2.f * juce::MathConstants<float>::pi * cutoffFreq / this->sampleRate;
    float alpha = std::sin(w) / (2.f * 1.f); // Q = 1

    float b0 = (1.f - std::cos(w)) / 2.f;
    float b1 = 1.f - std::cos(w);
    float b2 = b0;
    float a0 = 1.f + alpha;
    float a1 = -2.f * std::cos(w);
    float a2 = 1.f - alpha;

    FMatrix ba = { { b0, b1, b2 }, { a0, a1, a2 } };

    // Normalisation:
    for (int i = 0; i < ba.size(); i++) { for (int j = 0; j < ba[0].size(); j++) { ba[i][j] /= a0; } }

    return ba;
}

void Distortion::applyLPF(juce::AudioBuffer<float>& buffer, int ch, int n, double cutoff, FMatrix& previousX, FMatrix& previousY) {

    auto* channelDataWrite = buffer.getWritePointer(ch);
    auto* channelDataRead = buffer.getReadPointer(ch);

    float xN1, xN2, yN1, yN2, b0, b1, b2, a1, a2;

    FMatrix coefficients = getLPFCoefficients(cutoff);

    xN1 = previousX[ch][0];
    xN2 = previousX[ch][1];
    yN1 = previousY[ch][0];
    yN2 = previousY[ch][1];
    b0 = coefficients[0][0];
    b1 = coefficients[0][1];
    b2 = coefficients[0][2];
    a1 = coefficients[1][1];
    a2 = coefficients[1][2];

    previousX[ch][0] = previousX[ch][1];
    previousX[ch][1] = channelDataRead[n];

    channelDataWrite[n] = b0 * channelDataRead[n] + b1 * xN2 + b2 * xN1 - a1 * yN2 - a2 * yN1;

    previousY[ch][0] = previousY[ch][1];
    previousY[ch][1] = channelDataRead[n];
}

FMatrix Distortion::getBPFCoefficients(float cutoffFreq) {

    float w = 2.f * juce::MathConstants<float>::pi * cutoffFreq / this->sampleRate;
    float alpha = std::sin(w) / (2.f * 1.f); // Q = 1

    float b0 = 1.f * alpha;
    float b1 = 0.f;
    float b2 = - 1.f * alpha;
    float a0 = 1.f + alpha;
    float a1 = -2.f * std::cos(w);
    float a2 = 1.f - alpha;

    FMatrix ba = { { b0, b1, b2 }, { a0, a1, a2 } };

    // Normalisation:
    for (int i = 0; i < ba.size(); i++) { for (int j = 0; j < ba[0].size(); j++) { ba[i][j] /= a0; } }

    return ba;
}

void Distortion::applyBPF(juce::AudioBuffer<float>& buffer, int ch, int n, double cutoff, FMatrix& previousX, FMatrix& previousY) {

    auto* channelDataWrite = buffer.getWritePointer(ch);
    auto* channelDataRead = buffer.getReadPointer(ch);

    float xN1, xN2, yN1, yN2, b0, b1, b2, a1, a2;

    FMatrix coefficients = getBPFCoefficients(cutoff);

    xN1 = previousX[ch][0];
    xN2 = previousX[ch][1];
    yN1 = previousY[ch][0];
    yN2 = previousY[ch][1];
    b0 = coefficients[0][0];
    b1 = coefficients[0][1];
    b2 = coefficients[0][2];
    a1 = coefficients[1][1];
    a2 = coefficients[1][2];

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
