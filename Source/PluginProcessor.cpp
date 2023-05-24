/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <juce_audio_utils/juce_audio_utils.h>

//==============================================================================
FootprintAudioProcessor::FootprintAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
apvts(*this, nullptr, "Parameters",
#include "Parametres.h"
)
{
    //updateParameters();
    //compressor.setRatio(&compressorRatio);
    //compressor.setAttack(&compressorAttack);
    //compressor.setRelease(&compressorRelease);
    //compressor.setThreshold(&compressorThreshold);

}

FootprintAudioProcessor::~FootprintAudioProcessor()
{
}

//==============================================================================
const juce::String FootprintAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FootprintAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FootprintAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FootprintAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FootprintAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FootprintAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FootprintAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FootprintAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FootprintAudioProcessor::getProgramName (int index)
{
    return {};
}

void FootprintAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FootprintAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    //updateParameters();
    //compressor.prepare(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
    rmsInLevelLeft.reset(sampleRate, 0.5);
    rmsInLevelRight.reset(sampleRate, 0.5);
    rmsOutLevelLeft.reset(sampleRate, 0.5);
    rmsOutLevelRight.reset(sampleRate, 0.5);

    rmsInLevelLeft.setCurrentAndTargetValue(-100.0f);
    rmsInLevelRight.setCurrentAndTargetValue(-100.0f);
    rmsOutLevelLeft.setCurrentAndTargetValue(-100.0f);
    rmsOutLevelRight.setCurrentAndTargetValue(-100.0f);

}

void FootprintAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FootprintAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FootprintAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    //////////////////////////////////////////////// input WAVEFORM VIEWER //////////////////////////////////////////////////
    if (displaySection != nullptr){
        displaySection->inputWaveform.pushBuffer(buffer);
    }

    /////////////////////////////////////////////INPUT RMS LEVEL METER//////////////////////////////////////////////////
    juce::ScopedNoDenormals noInDenormals;
    rmsInLevelLeft.skip(buffer.getNumSamples());
    rmsInLevelRight.skip(buffer.getNumSamples());
    {
        const auto value = juce::Decibels::gainToDecibels(buffer.getRMSLevel(0, 0, buffer.getNumSamples()));
        if (value < rmsInLevelLeft.getCurrentValue())
        {
            rmsInLevelLeft.setTargetValue(value);
        }
        else
            rmsInLevelLeft.setCurrentAndTargetValue(value);
    }

    {
        const auto value = juce::Decibels::gainToDecibels(buffer.getRMSLevel(0, 0, buffer.getNumSamples()));
        if (value < rmsInLevelRight.getCurrentValue())
        {
            rmsInLevelRight.setTargetValue(value);
        }
        else
            rmsInLevelRight.setCurrentAndTargetValue(value);
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    //updateParameters();
    //compressor.processBlock(buffer, midiMessages);


    //INSERT OTHER DSP EFFECTS PROCESS BLOCKS BEFORE THIS LINE

    /////////////////////////////////////////////OUTPUT RMS LEVEL METER//////////////////////////////////////////////////
    juce::ScopedNoDenormals noOutDenormals;
    rmsOutLevelLeft.skip(buffer.getNumSamples());
    rmsOutLevelRight.skip(buffer.getNumSamples());
    {
        const auto value = juce::Decibels::gainToDecibels(buffer.getRMSLevel(0, 0, buffer.getNumSamples()));
        if (value < rmsOutLevelLeft.getCurrentValue())
        {
            rmsOutLevelLeft.setTargetValue(value);
        }
        else
            rmsOutLevelLeft.setCurrentAndTargetValue(value);
    }

    {
        const auto value = juce::Decibels::gainToDecibels(buffer.getRMSLevel(0, 0, buffer.getNumSamples()));
        if (value < rmsOutLevelRight.getCurrentValue())
        {
            rmsOutLevelRight.setTargetValue(value);
        }
        else
            rmsOutLevelRight.setCurrentAndTargetValue(value);
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////// output WAVEFORM VIEWER //////////////////////////////////////////////////
    if (displaySection != nullptr){
        displaySection->outputWaveform.pushBuffer(buffer);
    }

}

//==============================================================================
bool FootprintAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FootprintAudioProcessor::createEditor()
{
    return new FootprintAudioProcessorEditor (*this);
}

//==============================================================================
void FootprintAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FootprintAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FootprintAudioProcessor();
}

APVTS::ParameterLayout FootprintAudioProcessor::createParameters(){
    
    auto attack = std::make_unique<juce::AudioParameterFloat>
    (juce::ParameterID {"Compressor_Attack", 1},
     "Compressor_Attack",
     juce::NormalisableRange<float>(0.001f, 0.5f, 0.002f, 1.f),
     0.01f);
    
    auto release = std::make_unique<juce::AudioParameterFloat>
    (juce::ParameterID {"Compressor_Release", 2},
     "Compressor_Release",
     juce::NormalisableRange<float>(0.001f, 0.5f, 0.002f, 1.f),
     0.01f);
    
    auto threshold = std::make_unique<juce::AudioParameterFloat>
    (juce::ParameterID {"Compressor_Threshold", 3},
     "Compressor_Threshold",
     juce::NormalisableRange<float>(-80.f, 20.f, 0.1f, 1.f),
     -35.f);
    
    auto ratio = std::make_unique<juce::AudioParameterInt>
    (juce::ParameterID {"Compressor_Ratio", 4},
     "Compressor_Ratio",
     1,
     15,
     10);
    
    return {std::move(attack), std::move(release), std::move(threshold), std::move(ratio)};
}


void FootprintAudioProcessor::updateParameters(){
    
    compressorAttack.set(apvts.getRawParameterValue("Compressor_Attack")->load());
    compressorRelease.set(apvts.getRawParameterValue("Compressor_Release")->load());
    compressorThreshold.set(apvts.getRawParameterValue("Compressor_Threshold")->load());
    compressorRatio.set(apvts.getRawParameterValue("Compressor_Threshold")->load());
    
}

float FootprintAudioProcessor::getInRmsValue(const int channel) const
{
    jassert(channel == 0 || channel == 1);
    if (channel == 0)
        return rmsInLevelLeft.getCurrentValue();
    if (channel == 1)
        return rmsInLevelRight.getCurrentValue();
    return 0.0f;
}

float FootprintAudioProcessor::getOutRmsValue(const int channel) const
{
    jassert(channel == 0 || channel == 1);
    if (channel == 0)
        return rmsOutLevelLeft.getCurrentValue();
    if (channel == 1)
        return rmsOutLevelRight.getCurrentValue();
    return 0.0f;
}

void FootprintAudioProcessor::setDisplaySection(DisplaySection* section)
{
    this->displaySection = section;
}
