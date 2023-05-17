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

void Reverb::prepare(double sampleRate, int samplesPerBlock){
    //Setup before execution. Executed when play is pressed
    
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
    auto totalNumInputChannels      = 2;                                            // Should be imported from somewhere
    auto totalNumOutputChannels     = 2;

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    
    juce::dsp::AudioBlock<float> block{ buffer };                                   // Create a block referencing the audio buffer


    for (int channel = 0; channel < block.getNumChannels(); ++channel) {            // Traverse channels. Mono reverb will be applied to each channel
        auto* channelData = block.getChannelPointer(channel); 
        //Now call reverb processing function (&channelData) - to be created
    }
}