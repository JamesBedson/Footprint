/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CompressorDSP.h"
//==============================================================================
/**
*/

using APVTS = juce::AudioProcessorValueTreeState;

class FootprintAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    
    //==============================================================================
    FootprintAudioProcessor();
    ~FootprintAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    APVTS apvts {*this, nullptr, "Pedal Parameters", createParameters()};
    
    float getInRmsValue(const int channel) const;
    float getOutRmsValue(const int channel) const;

private:
    APVTS::ParameterLayout createParameters();
    void updateParameters();
    
    juce::Atomic<float> compressorAttack;
    juce::Atomic<float> compressorRelease;
    juce::Atomic<float> compressorThreshold;
    juce::Atomic<int>   compressorRatio;
    
    Compressor compressor;
    
    //==============================================================================
    juce::LinearSmoothedValue<float> rmsInLevelLeft, rmsInLevelRight;
    juce::LinearSmoothedValue<float> rmsOutLevelLeft, rmsOutLevelRight;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FootprintAudioProcessor)
    
};
