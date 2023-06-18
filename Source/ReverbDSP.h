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

class CircularBuffer {

public:
    
    CircularBuffer(int fifoSize):fifo(fifoSize) {
        buffers.resize(fifoSize);
    }
    
    void prepare(int numChannels, int numSamples) {
        for (auto& buffer : buffers) {
            buffer.setSize(numChannels, numSamples, false, true, true);
            buffer.clear();
        }
    };

    bool push(const juce::AudioBuffer<float>& bufferToPush) {
        auto write = fifo.write(1);

        if (write.blockSize1 > 0) {
            buffers[write.startIndex1] = juce::AudioBuffer<float>(bufferToPush);
            return true;
        }
        return false;
    }
    
    void addToBuffer(const juce::AudioBuffer<float>& bufferToAdd,
                     const int blockIdx,
                     const int channelNum,
                     const int samplesPerBlock)
    {
        buffers[blockIdx].addFrom(channelNum, 0, bufferToAdd, channelNum, 0, samplesPerBlock);
    }
    
    void incrementWrite() {
        auto write = fifo.write(1);
    }

    bool pull(juce::AudioBuffer<float>& bufferToFill) {
        auto read = fifo.read(1);

        if (read.blockSize1 > 0) {
            bufferToFill = buffers[read.startIndex1];
            return true;
        }
        return false;
    }

    int getNumAvailableBuffers() const {
        return fifo.getNumReady();
    }

    std::vector<juce::AudioBuffer<float>> buffers;

private:
    juce::AbstractFifo fifo;
};


class Reverb : public AudioProcessingModule {
    
public:
    
    Reverb();
    ~Reverb() override;
    
    void prepare(double sampleRate, int samplesPerBlock, int numChannels) override;
    void processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer& midiMessages) override;
    
    void setWet(std::atomic<float>*);
    void setLowpassCutoff(std::atomic<float>*);
    void setHighpassCutoff(std::atomic<float>*);
    
private:
    // Global ==================================================
    const int numIRs;
    int calculateNextPow(int x);
    
    float wetValue;
    std::atomic<float>* wet;
    std::atomic<float>* lowpassCutoff;
    std::atomic<float>* highpassCutoff;
    
    std::vector<juce::AudioBuffer<float>> impulseResponses {
        juce::AudioBuffer<float>(),
        juce::AudioBuffer<float>(),
        juce::AudioBuffer<float>(),
        juce::AudioBuffer<float>()
    };
    
    // JUCE Convolver implementation ===========================
    
    juce::dsp::Convolution aranyoShort;
    juce::dsp::Convolution aranyoLarge;
    juce::dsp::Convolution bathroom;
    juce::dsp::Convolution corridor;
    
    // Modified FFT Implementation =============================
    
    /*
    juce::AudioBuffer<float> tempInputBuffer;
    juce::AudioBuffer<float> tempInputFFTBuffer;
    juce::AudioBuffer<float> bufferToAdd;
    
    std::unique_ptr<CircularBuffer> circularBuffer;
    
    std::vector<juce::AudioBuffer<float>> fftImpulseResponses {
        juce::AudioBuffer<float>(),
        juce::AudioBuffer<float>(),
        juce::AudioBuffer<float>(),
        juce::AudioBuffer<float>()
    };
    */
    
    // Original Implementation ==================================
    
    /*
    
    juce::dsp::AudioBlock<float> monoChannel;
    juce::dsp::AudioBlock<float> processedMonoChannel;
    
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
    
    int count;
    // Reverb buffer related variables
    int fftOrder; // = 17;
    int fftSize; // = 1 << fftOrder;
    int blockSize;
    int blocksIR;
     
    void processStereo(const juce::AudioBuffer<float>& inputBuffer, juce::AudioBuffer<float>& outputBuffer);

    void fft_IR(juce::AudioBuffer<float>& buffer_IR);
    juce::AudioBuffer<float> fft_block(juce::AudioBuffer<float>& buffer_IR);

    int calculateLog2(int x);
    int calculateNextPow(int x);
    void zero_pad(juce::AudioBuffer<float>& buffer_to_pad, int num_samples_to_pad);
    
    double sampleRate;
    //int samplesPerBlock;
    */
    
};
