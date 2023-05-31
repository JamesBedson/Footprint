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

    void processStereo(float* const left, float* const right, const int numSamples);

    void loadIR(std::string filePath);



    void setWet(std::atomic<float>*);
    void setLowpassCutoff(std::atomic<float>*);
    void setHighpassCutoff(std::atomic<float>*);
    
private:
    juce::dsp::AudioBlock<float> monoChannel;
    juce::dsp::AudioBlock<float> processedMonoChannel;
    int count = 0;
    int blocksIR;
    juce::AudioBuffer<float> revBuffer;
    juce::dsp::AudioBlock<float> revBlock;
    juce::AudioBuffer<float> impulseResponse;
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
