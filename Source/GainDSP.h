/*
  ==============================================================================

    Gain.h
    Created: 6 Jun 2023 11:58:52pm
    Author:  James Bedson

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "AudioProcessingModule.h"

class Gain : public AudioProcessingModule {
    
private:
    std::atomic<float>* gainValueLinear;
    
public:
    
    void setGainValue(std::atomic<float>* gainParam) {
        this->gainValueLinear = gainParam;
    }
    
    void prepare(double sampleRate, int samplesPerBlock, int numChannels) {
        
        
    }
    
    void processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer& midiMessages) {
        
        float gain = gainValueLinear->load();
        
        for (int ch = 0; ch < buffer.getNumChannels(); ch++) {
            auto* channelPtrWrite   = buffer.getWritePointer(ch);
            auto* channelPtrRead    = buffer.getReadPointer(ch);
            
            for (int n = 0; n < buffer.getNumSamples(); n++) {
                channelPtrWrite[n] = channelPtrRead[n] * gain;
            }
        }
    }

};
