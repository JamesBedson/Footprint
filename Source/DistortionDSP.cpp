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
    
}

void Distortion::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages){
    
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
