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

    // IR setup
    loadIR("../../IR_UPF_formated/48kHz/UPF_Aranyo_large_48kHz.wav");
    fftOrder = calculateLog2(impulseResponse.getNumSamples());
    fftSize = 1 << fftOrder;

    // Calculate FFT of the IR
    impulseResponse_fft.makeCopyOf(impulseResponse);
    fft_IR(impulseResponse_fft);
    
    // Reverb buffer setup
    blockSize = samplesPerBlock;
    blocksIR = ceil(fftSize / blockSize);
    revBuffer.setSize(numChannels, blocksIR * samplesPerBlock);
    revBuffer.clear();
    count = 0;

    // Get reverb buffer pointers
    revBufferWrite_L = revBuffer.getWritePointer(0);
    //revBufferWrite_R = revBuffer.getWritePointer(1);
    revBufferRead_L = revBuffer.getReadPointer(0);
    //revBufferRead_R = revBuffer.getReadPointer(1);
}

void Reverb::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages){
    if (this->isBypassed()) return;
    /*Some notes on implementation:
    The number of samples in these buffers is NOT guaranteed to be the same for every callback,
    and may be more or less than the estimated value given to prepareToPlay(). Your code must be able
    to cope with variable-sized blocks, or you're going to get clicks and crashes!

    Also note that some hosts will occasionally decide to pass a buffer containing zero samples,
    so make sure that your algorithm can deal with that!
    */

    // Get parameters
    wetValue = wet->load();

    // Get input data pointers
    auto* channelDataWrite_L = buffer.getWritePointer(0);
    auto* channelDataWrite_R = buffer.getWritePointer(1);
    auto* channelDataRead_L = buffer.getReadPointer(0);
    //auto* channelDataRead_R = buffer.getReadPointer(1);

    // Get IR data pointers
    auto* impulseResponseRead_L = impulseResponse_fft.getReadPointer(0);
    //auto* impulseResponseRead_R = impulseResponse_fft.getReadPointer(1);

    // Calculate returnBlock -> FFT(channelDataRead)
    returnBlock = fft_block(buffer);

    // Get returnBlock data pointers
    auto* returnBlockWrite_L = returnBlock.getWritePointer(0);
    //auto* returnBlockWrite_R = returnBlock.getWritePointer(1);
    auto* returnBlockRead_L = returnBlock.getReadPointer(0);
    //auto* returnBlockRead_R = returnBlock.getReadPointer(1);

    // Do the convolution FFT(returnBlock * impulseResponse)
    for (int sample = 0; sample < fftSize / 2; sample++)
    {
        returnBlockWrite_L[sample] = returnBlockRead_L[sample] * impulseResponseRead_L[sample];
        //returnBlockWrite_R[sample] = returnBlockRead_R[sample] * impulseResponseRead_R[sample];
    }

    // Calculate inverse FFT of the convolution
    juce::dsp::FFT inverseFFT(fftOrder);                                    // Create FFT object
    returnBlockWrite_L = returnBlock.getWritePointer(0);					// Get returnBlock data pointers 
    //returnBlockWrite_R = returnBlock.getWritePointer(1);

    inverseFFT.performRealOnlyInverseTransform(returnBlockWrite_L);		    // Perform inverse FFT
    //inverseFFT.performRealOnlyInverseTransform(returnBlockWrite_R);

    for (int sample = fftSize / 2; sample < 2 * fftSize - 1; sample++)      // Empty the unused return of the IFFT
    {
        returnBlock.setSample(0, sample, 0);
        //returnBlock.setSample(1, sample, 0);
    }
    
    // Get reverbBlock data pointers
    auto* reverbBlockWrite_L = reverbBlock.getWritePointer(0);
    //auto* reverbBlockWrite_R = reverbBlock.getWritePointer(1);
    auto* reverbBlockRead_L = reverbBlock.getReadPointer(0);
    //auto* reverbBlockRead_R = reverbBlock.getReadPointer(1);

    // Counter for the ciruclar offset.
    if (count >= blocksIR) {
        count = 0;
    }

    // Traversal of samples.
    for (int sample = 0;  sample < samplesPerBlock;  sample++)
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
            revBufferWrite_L[bufferPos] = revBufferRead_L[bufferPos] + 0.1f * returnBlockRead_L[channelPos];
            //revBufferWrite_R[bufferPos] = revBufferRead_R[bufferPos] + 0.1f * returnBlockRead_R[channelPos];
        }

        // Output addition.
        channelDataWrite_L[sample] = (1 - wetValue) * channelDataRead_L[sample] + wetValue * revBufferRead_L[sample + (count * samplesPerBlock)];
        channelDataWrite_R[sample] = (1 - wetValue) * channelDataRead_L[sample] + wetValue * revBufferRead_L[sample + (count * samplesPerBlock)];
        //channelDataWrite_R[sample] = (1 - wetValue) * channelDataRead_R[sample] + wetValue * revBufferRead_R[sample + (count * samplesPerBlock)];
        
        // Buffer clearance.
        revBuffer.setSample(0, sample + (count * samplesPerBlock), 0);  // Clear buffer at block #0. This is the block that will be renewed in the next iteration
        //revBuffer.setSample(1, sample + (count * samplesPerBlock), 0);
    }

    // Counter update.
    count += 1;
}

void Reverb::fft_IR(juce::AudioBuffer<float>& buffer_IR) {

    // Prepare the IR for the FFT
    juce::dsp::FFT forwardFFT(fftOrder);
    buffer_IR.setSize(buffer_IR.getNumChannels(), fftSize * 2, true, true, true);

    // Clean the second half of the IR buffer
    for (int frame = fftSize; frame < 2 * fftSize - 1; frame++)
    {
        buffer_IR.setSample(0, frame, 0);
        //buffer_IR.setSample(1, frame, 0);
    }

    // Get IR data pointers
    float* channelData_L = buffer_IR.getWritePointer(0);
    //float* channelData_R = buffer_IR.getWritePointer(1);

    // Perform FFT
    forwardFFT.performRealOnlyForwardTransform(channelData_L);
    //forwardFFT.performRealOnlyForwardTransform(channelData_R);
}

juce::AudioBuffer<float> Reverb::fft_block(juce::AudioBuffer<float>& buffer_block) {

    // Prepare the block for the FFT
    juce::dsp::FFT forwardFFT(fftOrder);

    // Zero pad the block to the size of the IR
    juce::AudioBuffer<float> padded_block;
    padded_block.makeCopyOf(buffer_block);
    zero_pad(padded_block, fftSize);
    padded_block.setSize(padded_block.getNumChannels(), fftSize * 2, true, true, true);

    // Clean the second half of the block buffer
    for (int frame = fftSize; frame < 2 * fftSize - 1; frame++)
    {
        padded_block.setSample(0, frame, 0);
        //padded_block.setSample(1, frame, 0);
    }

    // Get the block data pointers
    float* channelData_L = padded_block.getWritePointer(0);
    //float* channelData_R = padded_block.getWritePointer(1);

    // Perform FFT
    forwardFFT.performRealOnlyForwardTransform(channelData_L);
    //forwardFFT.performRealOnlyForwardTransform(channelData_R);

    return padded_block;
}

void Reverb::loadIR(const char* filePath) {

    juce::File IR_file = IR_file.getCurrentWorkingDirectory().getChildFile(filePath);

    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
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

int Reverb::calculateNextPow(int x)
{
    // Calculate next power of 2
    return pow(2, ceil(log(x) / log(2)));
}

void Reverb::zero_pad(juce::AudioBuffer<float>& buffer_to_pad, int num_samples_ir)
{
    int numChannels = buffer_to_pad.getNumChannels();
    int currentNumSamples = buffer_to_pad.getNumSamples();

    // Resize the buffer to accommodate the desired number of samples
    buffer_to_pad.setSize(numChannels, num_samples_ir, true, true, true);

    // Zero-pad each channel
    for (int sample = currentNumSamples; sample < num_samples_ir; sample++)
    {
        buffer_to_pad.setSample(0, sample, 0);
        buffer_to_pad.setSample(1, sample, 0);
    }
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
