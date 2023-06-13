/*
  ==============================================================================

    CompressorDSP.cpp
    Created: 15 May 2023 6:48:31pm
    Author:  James Bedson

  ==============================================================================
*/

#include "CompressorDSP.h"

Compressor::Compressor(){
    
}

Compressor::~Compressor(){
    
}

void Compressor::prepare(double sampleRate, int samplesPerBlock, int numChannels){
    
    attackReleaseAverager.setAttack(attack);
    attackReleaseAverager.setRelease(release);
    attackReleaseAverager.prepare(sampleRate, samplesPerBlock, numChannels);
    
    
}

void Compressor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages){
    if (this->isBypassed()) return;
    
    juce::AudioBuffer<float> gainEnvelope;
    gainEnvelope.makeCopyOf(buffer);
    
    // Computing Envelope/Detector
    for (int ch = 0; ch < buffer.getNumChannels(); ch++){
        auto* channelDataWrite  = gainEnvelope.getWritePointer(ch);
        auto* channelDataRead   = gainEnvelope.getReadPointer(ch);

        for (int n = 0; n < buffer.getNumSamples(); n++){
            channelDataWrite[n] = std::abs(channelDataRead[n]);
        }
    }
    
    attackReleaseAverager.processBlock(gainEnvelope, midiMessages);
    
    computeStaticCurve(gainEnvelope);
    
    for (int ch = 0; ch < buffer.getNumChannels(); ch++){
        
        auto* channelDataWrite  = buffer.getWritePointer(ch);
        auto* channelDataRead   = buffer.getReadPointer(ch);
        auto* envelopeDataRead  = gainEnvelope.getReadPointer(ch);
        
        for (int n = 0; n < buffer.getNumSamples(); n++){
            channelDataWrite[n] = envelopeDataRead[n] * channelDataRead[n];
        }
    }
}

void Compressor::computeStaticCurve(juce::AudioBuffer<float>& envelope){
    float slope     = 1 - 1/static_cast<int>(ratio->load());
    float th        = threshold->load();
    
    for (int ch = 0; ch < envelope.getNumChannels(); ch++){
        
        auto* channelDataWrite  = envelope.getWritePointer(ch);
        auto* channelDataRead   = envelope.getReadPointer(ch);
        
        for (int n = 0; n < envelope.getNumSamples(); n++){
            
            if (channelDataRead[n] == 0) channelDataWrite[n] = epsilonFloat;
            channelDataWrite[n] = 20 * std::log10f(channelDataRead[n]);
            
            if (channelDataRead[n] > th) channelDataWrite[n] = slope * (th - channelDataRead[n]);
            else channelDataWrite[n] = 0;
            
            channelDataWrite[n] = std::pow(10, channelDataRead[n] / 10);
        }
    }
}

void Compressor::setAttack(std::atomic<float> *attackPtr){
    this->attack = attackPtr;
}

void Compressor::setRelease(std::atomic<float> *releasePtr){
    this->release = releasePtr;
}

void Compressor::setRatio(std::atomic<float> *ratioPtr){
    this->ratio = ratioPtr;
}

void Compressor::setThreshold(std::atomic<float> *thresholdPtr){
    this->threshold = thresholdPtr;
}



