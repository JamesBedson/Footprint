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

    //loadIR("/Users/pausegalestorres/Desktop/Footprint/ReverbAudios/IR_UPF_formated/48kHz/UPF_Aranyo_large_48kHz.wav");
    //loadIR("C:/Downloads/IR_UPF_formated/48kHz/UPF_corridor_balloon_1_48kHz.wav");

    loadIR("../../IR_UPF_formated/48kHz/UPF_corridor_balloon_1_48kHz.wav");

    blockSize = samplesPerBlock;

    num_samples_ir = impulseResponse.getNumSamples();

    impulseResponse_fft.makeCopyOf(impulseResponse);
    fft_IR(impulseResponse_fft);

    num_samples_fft_ir = impulseResponse_fft.getNumSamples();
    
    // Reverb buffer setup
    
    blocksIR = ceil(fftSize / blockSize); //50;
    revBuffer.setSize(numChannels, blocksIR * samplesPerBlock);
    revBuffer.clear();
    count = 0;

    // Get reverb buffer pointers
    revBufferWrite = revBuffer.getWritePointer(0);
    revBufferRead = revBuffer.getReadPointer(0);

    //reverb.setSampleRate(sampleRate);
    //reverb.setParameters({0.9f, 0.9f, 0.9f, false});
}

void Reverb::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages){
    /*Some notes on implementation:
    The number of samples in these buffers is NOT guaranteed to be the same for every callback,
    and may be more or less than the estimated value given to prepareToPlay(). Your code must be able
    to cope with variable-sized blocks, or you're going to get clicks and crashes!

    Also note that some hosts will occasionally decide to pass a buffer containing zero samples,
    so make sure that your algorithm can deal with that!
    */

    //juce::ScopedNoDenormals noDenormals;                                          // Used by some tutorials, why?
    //auto totalNumInputChannels      = 2;                                            // Should be imported from somewhere
    //auto totalNumOutputChannels     = 2;

    //for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    //    buffer.clear(i, 0, buffer.getNumSamples());

    //juce::dsp::AudioBlock<float> block{ buffer };                                   // Create a block referencing the audio buffer

    //for (int channel = 0; channel < block.getNumChannels(); ++channel) {            // Traverse channels. Mono reverb will be applied to each channel
    //    monoChannel = block.getSingleChannelBlock(channel);
    //    //processedMonoChannel = processMono(monoChannel, midiMessages, sampleRate);
    //    processedMonoChannel.copyTo(buffer);
    //}

    // Get parameters
    wetValue = wet->load();

    // Get input data pointers
    auto* channelDataWrite = buffer.getWritePointer(0);
    auto* channelDataRead = buffer.getReadPointer(0);

    // Calculate reverbBlock -> FFT(channelDataRead)
    returnBlock = fft_block(buffer);

    //auto* impulseResponseRead = impulseResponse.getReadPointer(0);
    auto* impulseResponseRead = impulseResponse_fft.getReadPointer(0);
    //should this be impulseResponse_fft?

    auto* returnBlockWrite = returnBlock.getWritePointer(0);
    auto* returnBlockRead = returnBlock.getReadPointer(0);

    for (int sample = 0; sample < fftSize / 2; sample++) //maybe fftSize / 2?
    {
        returnBlockWrite[sample] = returnBlockRead[sample] * impulseResponseRead[sample];
    }



    juce::dsp::FFT inverseFFT(fftOrder);
    returnBlockWrite = returnBlock.getWritePointer(0);

    //buffer_IR.setSize(buffer_IR.getNumChannels(), fftSize * 2, true, true, true);

    /*for (int frame = fftSize; frame < 2 * fftSize - 1; frame++)
    {
        buffer_IR.setSample(0, frame, 0);
        buffer_IR.setSample(1, frame, 0);
    }*/

    //float* channelData_L = buffer_IR.getWritePointer(0);
    //float* channelData_R = buffer_IR.getWritePointer(1);

    inverseFFT.performRealOnlyInverseTransform(returnBlockWrite);

    for (int sample = fftSize / 2; sample < 2 * fftSize - 1; sample++)
    {
        returnBlock.setSample(0, sample, 0);
        returnBlock.setSample(1, sample, 0);
    }
    
    
    //returnBlock.setSize(returnBlock.getNumChannels(), fftSize, true, true, true);






    //juce::dsp::FFT fft_L(num_samples_fft_ir * 2);
    //juce::dsp::FFT fft_L(calculateLog2(num_samples_fft_ir / 2));
    //juce::dsp::FFT fft_R(calculateLog2(num_samples_fft_ir / 2));

    //reverbBlock.setSize(reverbBlock.getNumChannels(), num_samples_fft_ir * 2, true, true, true);
    //reverbBlockWrite = reverbBlock.getWritePointer(0);

    // Perform the FFT
    //fft_L.performRealOnlyInverseTransform(reverbBlockWrite);
    //fft_R.performRealOnlyForwardTransform(channelData_R);

    //reverbBlock.setSize(reverbBlock.getNumChannels(), num_samples_fft_ir, true, true, true);

    auto* reverbBlockWrite = reverbBlock.getWritePointer(0);
    auto* reverbBlockRead = reverbBlock.getReadPointer(0);

    // Counter for the ciruclar offset.
    if (count >= blocksIR) {
        count = 0;
    }

    // Traversal of samples.
    for (int sample = 0;  sample < samplesPerBlock;  sample++)
    //for (int sample = 0; sample < 1; sample++)
    {
        // Traversal of blocks. Blocks go always 0-blocksIR. An offset is set to the revBuffer.
        // This offset is a circular offset. To avoid creating an infinite revBuffer, samples are
        // overwritten in a circular way. The offset is calculated as (block + count) % blocksIR.
        for (int block = 0; block < blocksIR; block++)
        {
            // Position in the reverbBlock (does not take circular offset into account).
            int channelPos = sample + (block * samplesPerBlock);

            // Position in the revBuffer (takes circular offset into account).
            int offset = (block + count) % blocksIR;
            int bufferPos = sample + (offset * samplesPerBlock);

            // Update the revBuffer with the newly added reverb plus the previous exising reverb cue from past samples.
            //revBufferWrite[bufferPos] = revBufferRead[bufferPos] + channelDataRead[sample]; //DELETE! testing only 
            //revBufferWrite[bufferPos] = revBufferRead[bufferPos] + 5.0f*reverbBlockRead[channelPos]; //THIS is the line
            revBufferWrite[bufferPos] = revBufferRead[bufferPos] + 0.1f*returnBlockRead[channelPos]; //THIS is the line
        }

        // Output addition.
        channelDataWrite[sample] = (1 - wetValue) * channelDataRead[sample] + wetValue * revBufferRead[sample + (count * samplesPerBlock)];
        
        // Buffer clearance.
        revBuffer.setSample(0, sample + (count * samplesPerBlock), 0);  // Clear buffer at block #0. This is the block that will be renewed in the next iteration
    }

    // Counter update.
    count += 1;

    //processStereo(buffer.getWritePointer(0), buffer.getWritePointer(1), buffer.getNumSamples());
}

void Reverb::fft_IR(juce::AudioBuffer<float>& buffer_IR) {

    juce::dsp::FFT forwardFFT(fftOrder);

    buffer_IR.setSize(buffer_IR.getNumChannels(), fftSize * 2, true, true, true);

    for (int frame = fftSize; frame < 2 * fftSize - 1; frame++)
    {
        buffer_IR.setSample(0, frame, 0);
        buffer_IR.setSample(1, frame, 0);
    }

    float* channelData_L = buffer_IR.getWritePointer(0);
    float* channelData_R = buffer_IR.getWritePointer(1);

    forwardFFT.performRealOnlyForwardTransform(channelData_L);

    // Get the audio buffer information
    //num_samples_fft_ir = buffer_IR.getNumSamples();

    // Calculate the FFT size
    //int fft_size = calculateNextPow(num_samples_ir);

    //Resize the buffer for the FFT
    //buffer_IR.setSize(buffer_IR.getNumChannels(), fft_size * 2, true, true, true);

    //// Get the channel data
    //float* channelData_L = buffer_IR.getWritePointer(0);
    //float* channelData_R = buffer_IR.getWritePointer(1);

    //// Create a temporary buffer for FFT
    //juce::dsp::FFT fft_L(fft_size * 2);
    //juce::dsp::FFT fft_R(fft_size * 2);

    ////juce::dsp::FFT fft_L(calculateLog2(num_samples_ir / 2));
    ////juce::dsp::FFT fft_R(calculateLog2(num_samples_ir / 2));

    //// Perform the FFT
    //fft_L.performRealOnlyForwardTransform(channelData_L);
    //fft_R.performRealOnlyForwardTransform(channelData_R);

    //Resize the buffer for the FFT
    //buffer_IR.setSize(buffer_IR.getNumChannels(), fft_size, true, true, true);

    //juce::AudioBuffer<float> test = impulseResponse_fft;
    // Process the frequency domain data here (e.g., magnitude calculation, spectral processing)

    // Perform the inverse FFT (if needed)
    //fft.performRealOnlyInverseTransform(channelData);
}

juce::AudioBuffer<float> Reverb::fft_block(juce::AudioBuffer<float>& buffer_block) {

    juce::dsp::FFT forwardFFT(fftOrder);

    juce::AudioBuffer<float> padded_block;
    padded_block.makeCopyOf(buffer_block);

    zero_pad(padded_block, fftSize);

    padded_block.setSize(padded_block.getNumChannels(), fftSize * 2, true, true, true);

    for (int frame = fftSize; frame < 2 * fftSize - 1; frame++)
    {
        padded_block.setSample(0, frame, 0);
        padded_block.setSample(1, frame, 0);
    }

    float* channelData_L = padded_block.getWritePointer(0);
    float* channelData_R = padded_block.getWritePointer(1);

    forwardFFT.performRealOnlyForwardTransform(channelData_L);


    //juce::AudioBuffer<float> padded_block;
    //padded_block.makeCopyOf(buffer_block);

    //zero_pad(padded_block, num_samples_fft_ir);

    //// Get the channel data
    //float* channelData_L = padded_block.getWritePointer(0);
    //float* channelData_R = padded_block.getWritePointer(1);

    ////const int numSamples = padded_block.getNumSamples();

    //// Create a temporary buffer for 
    ////juce::dsp::FFT fft_L(num_samples_fft_ir);
    ////juce::dsp::FFT fft_R(num_samples_fft_ir);

    //int log2 = calculateLog2(num_samples_fft_ir / 2);

    //juce::dsp::FFT fft_L(10);
    ////juce::dsp::FFT fft_R(log2);

    //// Perform the FFT
    //fft_L.performRealOnlyForwardTransform(channelData_L);
    //fft_R.performRealOnlyForwardTransform(channelData_R);

    //padded_block.setSize(padded_block.getNumChannels(), num_samples_fft_ir, true, true, true);

    return padded_block;
}

void Reverb::loadIR(const char* filePath) {

    juce::File IR_file = IR_file.getCurrentWorkingDirectory().getChildFile(filePath);

    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    //juce::AudioFormatReader* reader = formatManager.createReaderFor(IR_file);
    juce::AudioFormatReader* reader = formatManager.createReaderFor(IR_file);
    
    if (reader != nullptr) {
        const int numSamples = reader->lengthInSamples;
        const int numChannelsIR = reader->numChannels;
        impulseResponse.setSize(numChannelsIR, numSamples);

        reader->read(&impulseResponse, 0, numSamples, 0, true, true);
        //delete reader;
    }
}

int Reverb::calculateLog2(int x)
{
    // Calculate the log base e (natural logarithm) of x
    float logE = std::log(x);

    // Calculate the log base e of 2
    float log2E = std::log(2);

    // Calculate the log base 2 of x by dividing logE by log2E
    int log2Value = logE / log2E;

    return log2Value;
}

int Reverb::calculateNextPow(int x) {
    return pow(2, ceil(log(x) / log(2)));
}

void Reverb::zero_pad(juce::AudioBuffer<float>& buffer_to_pad, int num_samples_ir)
{
    int numChannels = buffer_to_pad.getNumChannels();
    int currentNumSamples = buffer_to_pad.getNumSamples();

    //int numSamplesToAdd = num_samples_to_pad - currentNumSamples;

    // Resize the buffer to accommodate the desired number of samples
    buffer_to_pad.setSize(numChannels, num_samples_ir, true, true, true);

    // Zero-pad each channel
    for (int sample = currentNumSamples; sample < num_samples_ir; sample++)
    {
        buffer_to_pad.setSample(0, sample, 0);
        buffer_to_pad.setSample(1, sample, 0);
    }
    
    //for (int channel = 0; channel < numChannels; ++channel)
    //{
    //    float* channelData = buffer_to_pad.getWritePointer(channel);

    //    // Set the added samples to zero
    //    std::memset(channelData + currentNumSamples, 0, numSamplesToAdd * sizeof(float));
    //}
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
