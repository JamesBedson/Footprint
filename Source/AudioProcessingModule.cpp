/*
  ==============================================================================

    AudioProcessingModule.cpp
    Created: 15 May 2023 6:32:20pm
    Author:  James Bedson

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AudioProcessingModule.h"

//==============================================================================
AudioProcessingModule::AudioProcessingModule(){
    
    
}

AudioProcessingModule::~AudioProcessingModule(){
    
}

void AudioProcessingModule::setBypassParam(std::atomic<float> *bypassParam){
    this->bypassed = bypassParam;
}

bool AudioProcessingModule::isBypassed() {
    return this->bypassed->load();
}
