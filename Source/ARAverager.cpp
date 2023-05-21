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
    
    alphaA = std::exp(-1.f / (sampleRate * attack));
    alphaR = std::exp(-1.f / (sampleRate * release));
    
    previousOuts.resize(numChannels);
    
    for (int ch = 0; ch < numChannels; ch++){
        previousOuts[ch] = 0.f;
    }
    
}

void ARAverager::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages){
    
    for (int ch = 0; ch < buffer.getNumChannels(); ch++){
        
        auto* channelReadPtr    = buffer.getReadPointer(ch);
        auto* channelWritePTR   = buffer.getWritePointer(ch);
        float alphaToUse        = MIN_TIME_CONST;
        
        for (int n = 0; n < buffer.getNumSamples(); n++){
            
            if (n != 0) previousOuts[ch] = channelReadPtr[n - 1];
            
            if (previousOuts[ch] > channelReadPtr[n]) alphaToUse = alphaA;
            else alphaToUse = alphaR;
            
            channelWritePTR[n] = (1 - alphaToUse) * channelReadPtr[n] + alphaToUse * previousOuts[ch];
            juce::dsp::IIR::Coefficients<float> coeffs;
        }
    }
}

void ARAverager::setAttack(double attack){
    jassert(attack > MIN_TIME_CONST);
    this->attack    = attack;
}

void ARAverager::setRelease(double release){
    jassert(release > MIN_TIME_CONST);
    this->release   = release;
}
