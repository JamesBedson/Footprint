/*
  ==============================================================================

    ReverbDSP.cpp
    Created: 17 May 2023 5:35:08pm
    Author:  Pau Segalés Torres

  ==============================================================================
*/

#include "ReverbDSP.h"

Reverb::Reverb()
: numIRs(4)

{
    
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    std::vector<juce::AudioFormatReader*> readers;
    
    auto bathroom       = std::make_unique<juce::MemoryInputStream>(BinaryData::UPF_toilete_48kHz_wav,
                                                                    BinaryData::UPF_toilete_48kHz_wavSize,
                                                                    false);
    
    auto aranyoShort    = std::make_unique<juce::MemoryInputStream>(BinaryData::UPF_Aranyo_short_48kHz_wav,
                                                                    BinaryData::UPF_Aranyo_short_48kHz_wavSize,
                                                                    false);
    
    auto aranyoLarge    = std::make_unique<juce::MemoryInputStream>(BinaryData::UPF_Aranyo_large_48kHz_wav,
                                                                    BinaryData::UPF_Aranyo_large_48kHz_wavSize,
                                                                    false);
    
    auto tanger         = std::make_unique<juce::MemoryInputStream>(BinaryData::UPF_corridor_balloon_1_48kHz_wav,
                                                                    BinaryData::UPF_corridor_balloon_1_48kHz_wavSize,
                                                                    false);
    
    readers.push_back(formatManager.createReaderFor(std::move(bathroom)));
    readers.push_back(formatManager.createReaderFor(std::move(aranyoShort)));
    readers.push_back(formatManager.createReaderFor(std::move(aranyoLarge)));
    readers.push_back(formatManager.createReaderFor(std::move(tanger)));
    
    for (int irIndex = 0; irIndex < numIRs; irIndex++) {
        auto* currentReader = readers.at(irIndex);
        
        if (currentReader != nullptr) {
            const int numSamples        = static_cast<int>(currentReader->lengthInSamples);
            
            const int numChannelsIR     = currentReader->numChannels;
            auto& currentBuffer         = impulseResponses.at(irIndex);
            
            const int nextPower2        = calculateNextPow(numSamples);
            currentBuffer.setSize(numChannelsIR, nextPower2);
            currentBuffer.clear();
            
            currentReader->read(&currentBuffer, 0, numSamples, 0, true, true);
            delete currentReader;
        }
    }
}

Reverb::~Reverb(){
    
}

void Reverb::prepare(double sampleRate, int samplesPerBlock, int numChannels){
    
    for (int irIdx = 0; irIdx < impulseResponses.size(); irIdx++) {
        
        auto& currentImpulseResponseTime    = impulseResponses[irIdx];
        auto& currentImpulseResponseFreq    = fftImpulseResponses[irIdx];
        currentImpulseResponseFreq.setSize(currentImpulseResponseTime.getNumChannels(),
                                           currentImpulseResponseTime.getNumSamples() * 2);
        
        const int maxNumBlocks = static_cast<int>(currentImpulseResponseTime.getNumSamples() / samplesPerBlock);
        
        const int fftOrder = std::log2(samplesPerBlock);
        juce::dsp::FFT forwardFFT {fftOrder};
        
        for (int blockIdx = 0; blockIdx < maxNumBlocks; blockIdx++) {
            
            juce::AudioBuffer<float> tempIRBuffer;
            tempIRBuffer.setSize(numChannels, samplesPerBlock * 2);
            tempIRBuffer.clear();
            
            for (int ch = 0; ch < numChannels; ch++) {
                
                tempIRBuffer.copyFrom(ch, 0, currentImpulseResponseTime, ch, blockIdx * samplesPerBlock, samplesPerBlock);
                
                auto* tempIRWritePtr = tempIRBuffer.getWritePointer(ch);
                forwardFFT.performRealOnlyForwardTransform(tempIRWritePtr);
                
                currentImpulseResponseFreq.copyFrom(ch, blockIdx * samplesPerBlock * 2, tempIRBuffer, ch, 0, samplesPerBlock * 2);
            }
            
        }
    }
    
    
    
    
    
    
    /* ============================== OLD
    
    //return;
    //Setup before execution. Executed when play is pressed
    this->sampleRate        = sampleRate;
    this->samplesPerBlock   = samplesPerBlock;
    
    auto& impulseResponse   = impulseResponses[0];
    impulseResponse_fft     = fftImpulseResponses[0];
    
    // Calculate FFT of the IR
    
    fftOrder = calculateLog2(impulseResponse.getNumSamples());
    fftSize = 1 << fftOrder;

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
    
    */
}

void Reverb::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages){
    if (this->isBypassed()) return;
    if (buffer.getNumSamples() == 0) return;
    //if (buffer.getNumSamples() != samplesPerBlock) return;

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
    for (int sample = 0; sample < 2 * fftSize; sample++)
    {
        returnBlockWrite_L[sample] = returnBlockRead_L[sample] * impulseResponseRead_L[sample];
        //returnBlockWrite_R[sample] = returnBlockRead_R[sample] * impulseResponseRead_R[sample];
        
        if (returnBlockRead_L[sample] > lowpassCutoff->load()) {            // Este tipo de filtro no funciona
			returnBlockWrite_L[sample] = 0 * returnBlockRead_L[sample];
		}
        if (returnBlockRead_L[sample] < highpassCutoff->load()) {
            returnBlockWrite_L[sample] = 0 * returnBlockRead_L[sample];
        }
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
            revBufferWrite_L[bufferPos] = revBufferRead_L[bufferPos] + 0.05f * returnBlockRead_L[channelPos];
            //revBufferWrite_L[bufferPos] = revBufferRead_L[bufferPos] + returnBlockRead_L[channelPos];
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
