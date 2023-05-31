/*
  ==============================================================================

    ReverbDSP.cpp
    Created: 17 May 2023 5:35:08pm
    Author:  Pau Segalés Torres

  ==============================================================================
*/

#include "ReverbDSP.h"

Reverb::Reverb(){
    
}

Reverb::~Reverb(){
    
}

void Reverb::prepare(double sampleRate, int samplesPerBlock, int numChannels){
    //Setup before execution. Executed when play is pressed
    this->sampleRate = sampleRate;
    this->samplesPerBlock = samplesPerBlock;

    loadIR("/Users/pausegalestorres/Desktop/Footprint/ReverbAudios/IR_UPF_formated/48kHz/UPF_corridor_balloon_1_48kHz.wav");
    blockSize = samplesPerBlock;
    
    impulseResponse_fft.makeCopyOf(impulseResponse);
    fft_IR(impulseResponse_fft);
    
    intermediateBuffer.setSize(impulseResponse_fft.getNumChannels(), impulseResponse_fft.getNumSamples());
    
    //reverb.setSampleRate(sampleRate);
    //reverb.setParameters({0.9f, 0.9f, 0.9f, false});
}

void Reverb::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages)
{
    auto* channelDataWrite = buffer.getWritePointer(0);
    auto* channelDataRead = buffer.getReadPointer(0);
    
    
}

void Reverb::fft_IR(juce::AudioBuffer<float> &buffer_IR){
    // Get the audio buffer information
    num_samples_fft_ir = buffer_IR.getNumSamples();

   
    // Get the channel data
    float* channelData_L = buffer_IR.getWritePointer(0);
    float* channelData_R = buffer_IR.getWritePointer(1);

    
    // Create a temporary buffer for FFT
    juce::dsp::FFT fft_L (calculateLog2(num_samples_fft_ir/2)) ;
    juce::dsp::FFT fft_R (calculateLog2(num_samples_fft_ir/2)) ;

    // Perform the FFT
    fft_L.performRealOnlyForwardTransform(channelData_L);
    fft_R.performRealOnlyForwardTransform(channelData_R);

    juce::AudioBuffer<float> test = impulseResponse_fft;
    // Process the frequency domain data here (e.g., magnitude calculation, spectral processing)

    // Perform the inverse FFT (if needed)
    //fft.performRealOnlyInverseTransform(channelData);
}

void Reverb::fft_block(juce::AudioBuffer<float> &buffer_IR){
    // Get the audio buffer information
    const int numSamples = buffer_IR.getNumSamples();

   
    // Get the channel data
    float* channelData_L = buffer_IR.getWritePointer(0);
    float* channelData_R = buffer_IR.getWritePointer(1);

    
    // Create a temporary buffer for FFT
    juce::dsp::FFT fft_L (calculateLog2(numSamples/2)) ;
    juce::dsp::FFT fft_R (calculateLog2(numSamples/2)) ;

    // Perform the FFT
    fft_L.performRealOnlyForwardTransform(channelData_L);
    fft_R.performRealOnlyForwardTransform(channelData_R);

    juce::AudioBuffer<float> test = impulseResponse_fft;
    // Process the frequency domain data here (e.g., magnitude calculation, spectral processing)

    // Perform the inverse FFT (if needed)
    //fft.performRealOnlyInverseTransform(channelData);
}




void Reverb::loadIR(std::string filePath) {

    juce::File IR_file(filePath);

    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    juce::AudioFormatReader* reader = formatManager.createReaderFor(IR_file);

    if (reader != nullptr){
        const int numSamples = reader->lengthInSamples;
        const int numChannelsIR = reader->numChannels;
        impulseResponse.setSize(numChannelsIR, numSamples);
        
        reader->read(&impulseResponse, 0, numSamples, 0, true, true);
        //delete reader;
    }
}

void Reverb::processStereo(const juce::AudioBuffer<float>& inputBuffer, juce::AudioBuffer<float>& outputBuffer)
{
    
}






void Reverb::setWet(std::atomic<float>* wetParam){
    this->wet = wetParam;
}

void Reverb::setLowpassCutoff(std::atomic<float>* lowpassCutoff){
    this->lowpassCutoff = lowpassCutoff;
}

void Reverb::setHighpassCutoff(std::atomic<float>* highpassCutoff){
    this->highpassCutoff = highpassCutoff;
}


int Reverb::calculateLog2(int x)
{
    // Calculate the log base e (natural logarithm) of x
    int logE = std::log(x);

    // Calculate the log base e of 2
    int log2E = std::log(2);

    // Calculate the log base 2 of x by dividing logE by log2E
    int log2Value = logE / log2E;

    return log2Value;
}

juce::AudioBuffer<float> Reverb::zero_pad( juce::AudioBuffer<float> buffer_to_pad, int num_samples_to_pad){
    
    juce::AudioBuffer<float> concatenated (1, buffer_to_pad.getNumSamples() + num_samples_to_pad);
    juce::AudioBuffer<float> empty (1, num_samples_to_pad);
    
    concatenated.addFrom(0, 0, buffer_to_pad.getReadPointer(0), 0);
    
    return concatenated;
}

