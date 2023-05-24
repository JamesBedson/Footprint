/*
  ==============================================================================

    AudioProcessingModule.h
    Created: 15 May 2023 6:32:20pm
    Author:  James Bedson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
//==============================================================================
/*
*/
class AudioProcessingModule
{
public:
    
    AudioProcessingModule();
    virtual ~AudioProcessingModule() = 0;
    
    virtual void prepare(double sampleRate, int samplesPerBlock, int numChannels) = 0;
    virtual void processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer& midiMessages) = 0;
    
private:
    
    
};
