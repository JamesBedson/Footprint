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
    
    virtual void prepare(double sampleRate, int samplesPerBlock) = 0;
    virtual void processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer& midiMessages, double sampleRate) = 0;
    
private:
    
    
};
