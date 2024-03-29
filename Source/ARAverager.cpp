/*
  ==============================================================================

    ARAverager.cpp
    Created: 21 May 2023 7:34:51pm
    Author:  James Bedson

  ==============================================================================
*/

#include "ARAverager.h"

ARAverager::ARAverager(){
    
}

ARAverager::~ARAverager(){
    
}

void ARAverager::prepare(double sampleRate, int samplesPerBlock, int numChannels){
    
    this->sampleRate = sampleRate;
    firstIteration = true;
    previousOuts.resize(numChannels);
    
    for (int ch = 0; ch < numChannels; ch++){
        previousOuts[ch] = 0.f;
    }
    
}

void ARAverager::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer&){
    
    alphaA = std::exp(-1.f / (sampleRate * attack->load()));
    alphaR = std::exp(-1.f / (sampleRate * release->load()));
    
    for (int ch = 0; ch < buffer.getNumChannels(); ch++){
        
        auto* channelReadPtr    = buffer.getReadPointer(ch);
        auto* channelWritePTR   = buffer.getWritePointer(ch);
        float alphaToUse        = MIN_TIME_CONST;
        
        for (int n = 0; n < buffer.getNumSamples(); n++){
            
            if (n != 0) previousOuts[ch] = channelReadPtr[n - 1];
            
            if (previousOuts[ch] > channelReadPtr[n]) alphaToUse = alphaA;
            else alphaToUse = alphaR;
            
            channelWritePTR[n] = (1 - alphaToUse) * channelReadPtr[n] + alphaToUse * previousOuts[ch];
            if (n == buffer.getNumSamples() - 1) previousOuts[ch] = channelReadPtr[n];
        }
    }
}

void ARAverager::setAttack(std::atomic<float>* attack){
    this->attack    = attack;
}

void ARAverager::setRelease(std::atomic<float>* release){
    this->release   = release;
}
