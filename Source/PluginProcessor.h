/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CompressorDSP.h"
#include "ReverbDSP.h"
#include "DistortionDSP.h"
#include "EnvelopeFilter.h"
#include "DisplaySection.h"
#include "ProcessingConstants.h"
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
    
    APVTS apvts;
    
    float getInRmsValue(const int channel) const;
    float getOutRmsValue(const int channel) const;
    
    DisplaySection* displaySection = nullptr;
    void setDisplaySection(DisplaySection* section);
    

private:
    APVTS::ParameterLayout createParameters();
    void updateParameters();
    void initParameters();
    
    // Compressor Parameters

    std::atomic<float>* attack1;
    std::atomic<float>* attack2;
    std::atomic<float>* attack3;
    std::atomic<float>* attack4;
   
    std::atomic<float>* release1;
    std::atomic<float>* release2;
    std::atomic<float>* release3;
    std::atomic<float>* release4;
    
    std::atomic<float>* threshold1;
    std::atomic<float>* threshold2;
    std::atomic<float>* threshold3;
    std::atomic<float>* threshold4;
    
    std::atomic<float>* ratio1;
    std::atomic<float>* ratio2;
    std::atomic<float>* ratio3;
    std::atomic<float>* ratio4;
    
    // Reverb Parameters
    std::atomic<float>* wetDryMix1;
    std::atomic<float>* wetDryMix2;
    std::atomic<float>* wetDryMix3;
    std::atomic<float>* wetDryMix4;
    
    std::atomic<float>* cutoffLowpass1;
    std::atomic<float>* cutoffLowpass2;
    std::atomic<float>* cutoffLowpass3;
    std::atomic<float>* cutoffLowpass4;
    
    std::atomic<float>* cutoffHighpass1;
    std::atomic<float>* cutoffHighpass2;
    std::atomic<float>* cutoffHighpass3;
    std::atomic<float>* cutoffHighpass4;
    
    // Distortion Parameters
    std::atomic<float>* distGain1;
    std::atomic<float>* distGain2;
    std::atomic<float>* distGain3;
    std::atomic<float>* distGain4;
    
    std::atomic<float>* level1;
    std::atomic<float>* level2;
    std::atomic<float>* level3;
    std::atomic<float>* level4;
    
    std::atomic<float>* tone1;
    std::atomic<float>* tone2;
    std::atomic<float>* tone3;
    std::atomic<float>* tone4;
    
    // Envelope Filter Parameters
    std::atomic<float>* quality1;
    std::atomic<float>* quality2;
    std::atomic<float>* quality3;
    std::atomic<float>* quality4;
    
    std::atomic<float>* sensitivity1;
    std::atomic<float>* sensitivity2;
    std::atomic<float>* sensitivity3;
    std::atomic<float>* sensitivity4;
    
    std::atomic<float>* cutoffThreshold1;
    std::atomic<float>* cutoffThreshold2;
    std::atomic<float>* cutoffThreshold3;
    std::atomic<float>* cutoffThreshold4;
    
    std::vector<std::unique_ptr<Compressor>>        compressorVector;
    std::vector<std::unique_ptr<EnvelopeFilter>>    envelopeFilterVector;
    std::vector<std::unique_ptr<Distortion>>        distortionVector;
    std::vector<std::unique_ptr<Reverb>>            reverbVector;
    
    //==============================================================================
    juce::LinearSmoothedValue<float> rmsInLevelLeft, rmsInLevelRight;
    juce::LinearSmoothedValue<float> rmsOutLevelLeft, rmsOutLevelRight;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FootprintAudioProcessor)
    
    void initCompressorParameters(const int& slotIdx);
    void initReverbParameters(const int& slotIdx);
    void initEnvelopeFilterParameters(const int& slotIdx);
    void initDistortionParameters(const int& slotIdx);
    
};
