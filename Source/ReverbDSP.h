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

    void processStereo(const juce::AudioBuffer<float>& inputBuffer, juce::AudioBuffer<float>& outputBuffer);

    void loadIR(std::string filePath);
    void fft_IR(juce::AudioBuffer<float>& buffer_IR);
    juce::AudioBuffer<float> fft_block(juce::AudioBuffer<float>& buffer_IR);

    int calculateLog2(int x);
    juce::AudioBuffer<float> zero_pad(juce::AudioBuffer<float> buffer_to_pad, int num_samples_to_pad);

    void setWet(std::atomic<float>*);
    void setLowpassCutoff(std::atomic<float>*);
    void setHighpassCutoff(std::atomic<float>*);
    
private:
    juce::dsp::AudioBlock<float> monoChannel;
    juce::dsp::AudioBlock<float> processedMonoChannel;

    juce::AudioBuffer<float> impulseResponse;
    juce::AudioBuffer<float> impulseResponse_fft;

    juce::AudioBuffer<float> block_fft;
    juce::AudioBuffer<float> reverbBlock;

    int num_samples_ir;
    int num_samples_fft_ir;

    int blockSize;
    
    // Reverb buffer related variables
    juce::AudioBuffer<float> revBuffer;
    int count = 0;
    int blocksIR;
    float* revBufferWrite;
    const float* revBufferRead;


    //juce::dsp::AudioBlock<float> revBlock;
    //juce::AudioBuffer<float> impulseResponse;
    //juce::dsp::AudioBlock<float> processMono(juce::dsp::AudioBlock<float> channelData, double sampleRate, int samplesPerBlock);
    //juce::AudioBuffer<float> H_IR;
    //juce::dsp::Complex<float>* input;
    //juce::dsp::Complex<float>* inputSpectrum;
    //
    //static constexpr auto fftOrder = 10;                // [1]
    //static constexpr auto fftSize = 1 << fftOrder;      // [2]
    //juce::dsp::FFT forwardFFT;
    //std::array<float, fftSize> fifo;                    // [4]
    //std::array<float, fftSize * 2> fftData;             // [5]
    //int fifoIndex = 0;                                  // [6]
    //bool nextFFTBlockReady = false;                     // [7]
    
    //juce::dsp::Reverb::Parameters params;
    
    
    //juce::Reverb reverb;

    //juce::dsp::Convolution convolution;

    std::atomic<float>* wet;
    std::atomic<float>* lowpassCutoff;
    std::atomic<float>* highpassCutoff;

    double sampleRate;
    int samplesPerBlock;
    
};
