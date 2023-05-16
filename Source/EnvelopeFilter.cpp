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
    juce::MidiBuffer& midiMessages) {

}

//Matrix EnvelopeFilter::getLPFCoefficients(double sampleRate,float cutoffFrequency, float qualityFactor) {
//    
//    double w     = 2.0 * juce::MathConstants<double>::pi * cutoffFrequency / sampleRate;
//    double alpha = std::sin(w) / (2.0 * qualityFactor);
//
//    double b0 = (1.0 - std::cos(w)) / 2.0;
//    double b1 = 1.0 - std::cos(w);
//    double b2 = b0;
//    double a0 = 1.0 + alpha;
//    double a1 = -2.0 * std::cos(w);
//    double a2 = 1.0 - alpha;
//
//    std::vector<double> b = { b0, b1, b2 };
//    std::vector<double> a = { a0, a1, a2 };
//
//    return Matrix{ b,a };
//}

juce::AudioBuffer<float> EnvelopeFilter::getAmplitudeEnvelope(const juce::AudioBuffer<float>& buffer, double sampleRate) {
    juce::AudioBuffer<float> ampBuffer;
    ampBuffer.makeCopyOf(buffer);
    for (int i = 0; i < ampBuffer.getNumSamples(); i++) {
        for (int j = 0; j < ampBuffer.getNumChannels(); j++) {ampBuffer.setSample(j, i, std::abs(ampBuffer.getSample(j, i)));}
    }

    int cutoff = 1000;
    //Matrix ba = getLPFCoefficients(sampleRate, cutoff, qualityFactor);

    //for (std::vector<double>& c : ba) { for (double& element : c) { element = element / ba[1][0]; } }


    juce::IIRFilter filter;
    filter.setCoefficients(juce::IIRCoefficients::makeLowPass(sampleRate, cutoff));
    for (int j = 0; j < ampBuffer.getNumChannels(); j++) { filter.processSamples(ampBuffer.getWritePointer(j), ampBuffer.getNumSamples()); }

    return ampBuffer;
}