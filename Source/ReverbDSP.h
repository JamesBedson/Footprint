/*
  ==============================================================================

    ReverbDSP.h
    Created: 17 May 2023 5:35:08pm
    Author:  Pau Segalés Torres

  ==============================================================================
*/

#pragma once
#include "AudioProcessingModule.h"
#include <JuceHeader.h>

class Reverb : AudioProcessingModule {
    
public:
    Reverb();
    ~Reverb() override;
    
    void prepare(double sampleRate, int samplesPerBlock, int numChannels) override;
    void processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer& midiMessages) override;
    
    void setWet(std::atomic<float>*);
    void setLowpassCutoff(std::atomic<float>*);
    void setHighpassCutoff(std::atomic<float>*);
    
private:
    juce::dsp::AudioBlock<float> monoChannel;
    juce::dsp::AudioBlock<float> processedMonoChannel;
    juce::dsp::AudioBlock<float> processMono(juce::dsp::AudioBlock<float> channelData, juce::MidiBuffer& midiMessages, double sampleRate);
    
    std::atomic<float>* wet;
    std::atomic<float>* lowpassCutoff;
    std::atomic<float>* highpassCutoff;
    
};
