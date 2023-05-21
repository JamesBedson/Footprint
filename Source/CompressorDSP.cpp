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
    
    attackReleaseAverager.prepare(sampleRate, samplesPerBlock, numChannels);
    
}

void Compressor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages){
    
    
    
}
