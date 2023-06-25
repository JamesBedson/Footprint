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
#include "GainDSP.h"
#include "MonoDSP.h"
#include "PassThrough.h"
#include "ProcessingConstants.h"
#include "CustomAudioParameters.h"
//==============================================================================
/**
*/

using APVTS = juce::AudioProcessorValueTreeState;


struct GUIBufferFifo{
    
    void prepare(int numChannels, int numSamples){
        
        for (auto& buffer : buffers) {
            buffer.setSize(numChannels, numSamples, false, true, true);
            buffer.clear();
        }
    };
    
    bool push(const juce::AudioBuffer<float>& bufferToPush) {
        
        auto write = fifo.write(1);
        
        if (write.blockSize1 > 0) {
            buffers[write.startIndex1] = bufferToPush;
            return true;
        }
        return false;
    }
    
    bool pull(juce::AudioBuffer<float>& bufferToFill) {
        
        auto read = fifo.read(1);
        
        if (read.blockSize1 > 0) {
            bufferToFill = buffers[read.startIndex1];
            return true;
        }
        return false;
    }
    
    int getNumAvailableBuffers() const {
        return fifo.getNumReady();
    }
    
    static constexpr int fifoSize = 35;
    std::array<juce::AudioBuffer<float>, fifoSize> buffers;
    juce::AbstractFifo fifo {fifoSize};
};


class FootprintAudioProcessor  : public juce::AudioProcessor, public juce::AudioProcessorValueTreeState::Listener
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
    int count = 0;
    float getInRmsValue(const int channel) const;
    float getOutRmsValue(const int channel) const;
    
    void parameterChanged (const juce::String& parameterID, float newValue) override;
    void assignActiveModules(const juce::String& paramID, int value);
    
    GUIBufferFifo guiFifoInput;
    GUIBufferFifo guiFifoOutput;
private:
    void initParameters();
    
    // Editor Controls
    std::atomic<float>* inputGain;
    std::atomic<float>* outputGain;
    
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
    
    std::atomic<float>* compressorBypass1;
    std::atomic<float>* compressorBypass2;
    std::atomic<float>* compressorBypass3;
    std::atomic<float>* compressorBypass4;
    
    // Reverb Parameters
    std::atomic<float>* wetDryMix1;
    std::atomic<float>* wetDryMix2;
    std::atomic<float>* wetDryMix3;
    std::atomic<float>* wetDryMix4;
    
    std::atomic<float>* reverbIRChoice1;
    std::atomic<float>* reverbIRChoice2;
    std::atomic<float>* reverbIRChoice3;
    std::atomic<float>* reverbIRChoice4;
    
    std::atomic<float>* reverbBypass1;
    std::atomic<float>* reverbBypass2;
    std::atomic<float>* reverbBypass3;
    std::atomic<float>* reverbBypass4;
    
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
    
    std::atomic<float>* distortionBypass1;
    std::atomic<float>* distortionBypass2;
    std::atomic<float>* distortionBypass3;
    std::atomic<float>* distortionBypass4;
    
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
    
    std::atomic<float>* envelopeFilterBypass1;
    std::atomic<float>* envelopeFilterBypass2;
    std::atomic<float>* envelopeFilterBypass3;
    std::atomic<float>* envelopeFilterBypass4;
    
    Gain inputGainModule;
    Gain outputGainModule;
    Mono monoStereoModule;
    
    std::vector<std::unique_ptr<Compressor>>        compressorVector;
    std::vector<std::unique_ptr<EnvelopeFilter>>    envelopeFilterVector;
    std::vector<std::unique_ptr<Distortion>>        distortionVector;
    std::vector<std::unique_ptr<Reverb>>            reverbVector;
    std::vector<std::unique_ptr<AudioPassThrough>>  audioPassThroughVector;
    
    std::vector<AudioProcessingModule*>             activeModules;
    
    //==============================================================================
    void updateRMSLevelMeter(const float decibelValue, juce::LinearSmoothedValue<float>& rmsLevel);
    juce::LinearSmoothedValue<float> rmsInLevelLeft, rmsInLevelRight;
    juce::LinearSmoothedValue<float> rmsOutLevelLeft, rmsOutLevelRight;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FootprintAudioProcessor)
    
    void initCompressorParameters(const int& slotIdx);
    void initReverbParameters(const int& slotIdx);
    void initEnvelopeFilterParameters(const int& slotIdx);
    void initDistortionParameters(const int& slotIdx);
    
};
