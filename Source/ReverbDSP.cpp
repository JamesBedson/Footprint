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

std::vector<float> roll_zero( std::vector<float>& x, int k) {
    std::vector<float> result;
    
    // Roll the array
    for (int i = k; i < x.size(); i++)      result.push_back(x[i]);
    
    // Zero out the last k elements
    for (int i = 0; i < k; i++)             result.push_back(0);
    
    return result;
}

std::vector<float> zeroPad(const  std::vector<float>& x, int k) {
    
    std::vector<float> result = x;

    // Zero padding the array
    for (int i = 0; i < k; i++)             result.push_back(0);

    return result;
}



void Reverb::prepare(double sampleRate, int samplesPerBlock){
    //Setup before execution. Executed when play is pressed
    reverb_sampleRate = sampleRate;
    reverb_samplesPerBlock = samplesPerBlock;
}

void Reverb::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages, double sampleRate){
    /*Some notes on implementation:
    The number of samples in these buffers is NOT guaranteed to be the same for every callback,
    and may be more or less than the estimated value given to prepareToPlay(). Your code must be able
    to cope with variable-sized blocks, or you're going to get clicks and crashes!

    Also note that some hosts will occasionally decide to pass a buffer containing zero samples,
    so make sure that your algorithm can deal with that!
    */

    buffer.clear();
    
}








//void Reverb::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages, double sampleRate){
//    /*Some notes on implementation:
//    The number of samples in these buffers is NOT guaranteed to be the same for every callback,
//    and may be more or less than the estimated value given to prepareToPlay(). Your code must be able
//    to cope with variable-sized blocks, or you're going to get clicks and crashes!
//
//    Also note that some hosts will occasionally decide to pass a buffer containing zero samples,
//    so make sure that your algorithm can deal with that!
//    */
//
//    //juce::ScopedNoDenormals noDenormals;                                          // Used by some tutorials, why?
//    auto totalNumInputChannels      = 2;                                            // Should be imported from somewhere
//    auto totalNumOutputChannels     = 2;
//
//    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
//        buffer.clear(i, 0, buffer.getNumSamples());
//
//    juce::dsp::AudioBlock<float> block{ buffer };                                   // Create a block referencing the audio buffer
//
//    for (int channel = 0; channel < block.getNumChannels(); ++channel) {            // Traverse channels. Mono reverb will be applied to each channel
//        monoChannel = block.getSingleChannelBlock(channel);
//        processedMonoChannel = processMono(monoChannel, midiMessages, sampleRate);
//        processedMonoChannel.copyTo(buffer);
//    }
//}
//
//juce::dsp::AudioBlock<float> Reverb::processMono(juce::dsp::AudioBlock<float> channelData, juce::MidiBuffer& midiMessages, double sampleRate) {
//
//
//    return channelData;
//}
