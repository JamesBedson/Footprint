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
    
    gainEnvelope.setSize(numChannels, samplesPerBlock);
    attackReleaseAveragerPre.setAttack(attack);
    attackReleaseAveragerPre.setRelease(release);
    attackReleaseAveragerPre.prepare(sampleRate, samplesPerBlock, numChannels);
    attackReleaseAveragerEnv.setAttack(attack);
    attackReleaseAveragerEnv.setRelease(release);
    attackReleaseAveragerEnv.prepare(sampleRate, samplesPerBlock, numChannels);
    
}

void Compressor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages){
    if (this->isBypassed()) return;
    
    gainEnvelope.makeCopyOf(buffer, true);
    
    // Computing Envelope/Detector
    for (int ch = 0; ch < buffer.getNumChannels(); ch++){
        auto* channelDataWrite  = gainEnvelope.getWritePointer(ch);
        auto* channelDataRead   = gainEnvelope.getReadPointer(ch);

        for (int n = 0; n < buffer.getNumSamples(); n++){
            channelDataWrite[n] = std::abs(channelDataRead[n]);
        }
    }
    
    //attackReleaseAveragerPre.processBlock(gainEnvelope, midiMessages);
    computeStaticCurve(gainEnvelope);
    attackReleaseAveragerEnv.processBlock(gainEnvelope, midiMessages);
    
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
    int ratioParam      = static_cast<int>(ratio->load());
    float slope         = 1 - 1/ratioParam;
    float th            = threshold->load();
    
    for (int ch = 0; ch < envelope.getNumChannels(); ch++){
        
        auto* envelopeDataWrite  = envelope.getWritePointer(ch);
        auto* envelopeDataRead   = envelope.getReadPointer(ch);
        
        for (int n = 0; n < envelope.getNumSamples(); n++){
            
            if (envelopeDataRead[n] == 0) envelopeDataWrite[n] = epsilonFloat;
            envelopeDataWrite[n] = 20 * std::log10f(envelopeDataRead[n]);
            
            if (envelopeDataRead[n] > th) envelopeDataWrite[n] = slope * (th - envelopeDataRead[n]);
            else envelopeDataWrite[n] = 0;
            
            envelopeDataWrite[n] = std::pow(10, envelopeDataRead[n] / 10);
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



