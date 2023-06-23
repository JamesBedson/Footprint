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

class Compressor : public AudioProcessingModule {
    
public:
    Compressor();
    ~Compressor() override;
    
    void prepare(double sampleRate, int samplesPerBlock, int numChannels) override;
    void processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer& midiMessages) override;
    void setAttack(std::atomic<float>* attackPtr);
    void setRelease(std::atomic<float>* releasePtr);
    void setThreshold(std::atomic<float>* thresholdPtr);
    void setRatio(std::atomic<float>* ratioPtr);

private:
    
    juce::AudioBuffer<float> gainEnvelope;
    std::atomic<float>* attack;
    std::atomic<float>* release;
    std::atomic<float>* threshold;
    std::atomic<float>* ratio;
    ARAverager attackReleaseAveragerPre, attackReleaseAveragerEnv;
    
    void computeStaticCurve(juce::AudioBuffer<float>&);
    
};



