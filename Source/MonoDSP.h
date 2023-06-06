/*
  ==============================================================================

    MonoDSP.h
    Created: 6 Jun 2023 11:59:22pm
    Author:  James Bedson

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "AudioProcessingModule.h"

class Mono : public AudioProcessingModule {

private:
    
public:
    
    void prepare(double sampleRate, int samplesPerBlock, int numChannels) {
        
    }
    
    void processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer& midiMessages) {
        
        if (buffer.getNumChannels() == 2) {
        
            auto leftChannelPtrWrite    = buffer.getWritePointer(0);
            auto rightChannelPtrWrite   = buffer.getWritePointer(1);
            auto leftChannelPtrRead     = buffer.getReadPointer(0);
            auto rightChannelPtrRead    = buffer.getReadPointer(1);
            
            for (int n = 0; n < buffer.getNumSamples(); n++) {
                
                auto leftTemp   = leftChannelPtrRead[n];
                auto rightTemp  = rightChannelPtrRead[n];
                leftChannelPtrWrite[n]  = (leftTemp + rightTemp) / 2;
                rightChannelPtrWrite[n] = (leftTemp + rightTemp) / 2;
            }
            
        }
        
    };

};
