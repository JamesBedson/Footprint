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

class Reverb : public AudioProcessingModule {
    
public:
    Reverb();
    ~Reverb() override;
    
    void prepare(double sampleRate, int samplesPerBlock, int numChannels) override;
    void processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer& midiMessages) override;

    void processStereo(const juce::AudioBuffer<float>& inputBuffer, juce::AudioBuffer<float>& outputBuffer);

    void loadIR(const char* filePath);
    void fft_IR(juce::AudioBuffer<float>& buffer_IR);
    juce::AudioBuffer<float> fft_block(juce::AudioBuffer<float>& buffer_IR);

    int calculateLog2(int x);
    int calculateNextPow(int x);
    void zero_pad(juce::AudioBuffer<float>& buffer_to_pad, int num_samples_to_pad);

    void setWet(std::atomic<float>*);
    void setLowpassCutoff(std::atomic<float>*);
    void setHighpassCutoff(std::atomic<float>*);
    
private:

    

    //juce::dsp::AudioBlock<float> monoChannel;
    //juce::dsp::AudioBlock<float> processedMonoChannel;

    // AudioBuffer initialization
    juce::AudioBuffer<float> impulseResponse;
    juce::AudioBuffer<float> impulseResponse_fft;

    juce::AudioBuffer<float> block_fft;
    juce::AudioBuffer<float> reverbBlock;
    juce::AudioBuffer<float> returnBlock;
    juce::AudioBuffer<float> revBuffer;
    float* revBufferWrite_L;
    float* revBufferWrite_R;
    const float* revBufferRead_L;
    const float* revBufferRead_R;    
       
    // Reverb buffer related variables
    int fftOrder; // = 17;
    int fftSize; // = 1 << fftOrder;
    int count = 0;
    int blockSize;
    int blocksIR;
    
    // Reverb parameters
    float wetValue;
    std::atomic<float>* wet;
    std::atomic<float>* lowpassCutoff;
    std::atomic<float>* highpassCutoff;

    double sampleRate;
    int samplesPerBlock;
    
};
