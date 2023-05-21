/*
  ==============================================================================

    CompressorDSP.h
    Created: 15 May 2023 6:48:31pm
    Author:  James Bedson

  ==============================================================================
*/

#pragma once
#include "AudioProcessingModule.h"
#include "ARAverager.h"
#include <JuceHeader.h>

constexpr float epsilonFloat = 1e-7f;

class Compressor : AudioProcessingModule {
    
public:
    Compressor();
    ~Compressor() override;
    
    void prepare(double sampleRate, int samplesPerBlock, int numChannels) override;
    void processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer& midiMessages) override;
    void setAttack(juce::Atomic<float>* attackPtr);
    void setRelease(juce::Atomic<float>* releasePtr);
    void setThreshold(juce::Atomic<float>* thresholdPtr);
    void setRatio(juce::Atomic<float>* ratioPtr);

private:
    
    juce::Atomic<float>* attack;
    juce::Atomic<float>* release;
    juce::Atomic<float>* threshold;
    juce::Atomic<float>* ratio;
    ARAverager attackReleaseAverager;
    
    void computeStaticCurve(juce::AudioBuffer<float>&);
    
};



