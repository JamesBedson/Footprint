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

    loadIR("aaa");
    
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

    processStereo(buffer.getWritePointer(0), buffer.getWritePointer(1), buffer.getNumSamples());
}

//juce::dsp::AudioBlock<float> Reverb::processMono(juce::dsp::AudioBlock<float> channelData, double sampleRate, int samplesPerBlock) {
//    
//    //input = channelData;
//    //juce::dsp::FFT::perform(input, inputSpectrum, false); //Perform FFT
//    
//
//    return channelData;
//}

void Reverb::processStereo(float* const left, float* const right, const int numSamples)
{

    for (auto i = 0; i < numSamples; i++) {
        for (auto j = 0; j < IRnumSamples; j++) {
            left[i]...
            right[i]...
        }
    }
    //JUCE_BEGIN_IGNORE_WARNINGS_MSVC(6011)
    //jassert(left != nullptr && right != nullptr);

    //for (int i = 0; i < numSamples; ++i)
    //{
    //    const float input = (left[i] + right[i]) * gain;
    //    float outL = 0, outR = 0;

    //    const float damp = damping.getNextValue();
    //    const float feedbck = feedback.getNextValue();

    //    for (int j = 0; j < numCombs; ++j)  // accumulate the comb filters in parallel
    //    {
    //        outL += comb[0][j].process(input, damp, feedbck);
    //        outR += comb[1][j].process(input, damp, feedbck);
    //    }

    //    for (int j = 0; j < numAllPasses; ++j)  // run the allpass filters in series
    //    {
    //        outL = allPass[0][j].process(outL);
    //        outR = allPass[1][j].process(outR);
    //    }

    //    const float dry = dryGain.getNextValue();
    //    const float wet1 = wetGain1.getNextValue();
    //    const float wet2 = wetGain2.getNextValue();

    //    left[i] = outL * wet1 + outR * wet2 + left[i] * dry;
    //    right[i] = outR * wet1 + outL * wet2 + right[i] * dry;
    //}
    //JUCE_END_IGNORE_WARNINGS_MSVC
}

void Reverb::loadIR(std::string filePath) {

    juce::File IR_file(filePath);

    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    juce::AudioFormatReader* reader = formatManager.createReaderFor(IR_file);

    if (reader != nullptr){
        
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
