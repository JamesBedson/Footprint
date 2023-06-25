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
#include "Parameters.h"
)
{
    initParameters();
    compressorVector.resize(4);
    reverbVector.resize(4);
    envelopeFilterVector.resize(4);
    distortionVector.resize(4);
    activeModules.resize(4);
    audioPassThroughVector.resize(4);
    
    inputGainModule.setGainValue(inputGain);
    outputGainModule.setGainValue(outputGain);
    
    for (int slotIdx = 0; slotIdx < 4; slotIdx++){
        
        compressorVector[slotIdx] = std::make_unique<Compressor>();
        initCompressorParameters(slotIdx);
        
        envelopeFilterVector[slotIdx] = std::make_unique<EnvelopeFilter>();
        initEnvelopeFilterParameters(slotIdx);
        
        reverbVector[slotIdx] = std::make_unique<Reverb>();
        initReverbParameters(slotIdx);
        
        distortionVector[slotIdx] = std::make_unique<Distortion>();
        initDistortionParameters(slotIdx);
        
        audioPassThroughVector[slotIdx] = std::make_unique<AudioPassThrough>();
    }
    
    apvts.addParameterListener(ProcessingConstants::Pedals::Identifiers::slot1Param, this);
    apvts.addParameterListener(ProcessingConstants::Pedals::Identifiers::slot2Param, this);
    apvts.addParameterListener(ProcessingConstants::Pedals::Identifiers::slot3Param, this);
    apvts.addParameterListener(ProcessingConstants::Pedals::Identifiers::slot4Param, this);
    
    
}

FootprintAudioProcessor::~FootprintAudioProcessor()
{
    apvts.removeParameterListener(ProcessingConstants::Pedals::Identifiers::slot1Param, this);
    apvts.removeParameterListener(ProcessingConstants::Pedals::Identifiers::slot2Param, this);
    apvts.removeParameterListener(ProcessingConstants::Pedals::Identifiers::slot3Param, this);
    apvts.removeParameterListener(ProcessingConstants::Pedals::Identifiers::slot4Param, this);
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
    //setLatencySamples(4096*32);
    guiFifoInput.prepare(getTotalNumInputChannels(), samplesPerBlock);
    guiFifoOutput.prepare(getTotalNumInputChannels(), samplesPerBlock);
    
    rmsInLevelLeft.reset(sampleRate, 0.5);
    rmsInLevelRight.reset(sampleRate, 0.5);
    rmsOutLevelLeft.reset(sampleRate, 0.5);
    rmsOutLevelRight.reset(sampleRate, 0.5);

    rmsInLevelLeft.setCurrentAndTargetValue(-100.0f);
    rmsInLevelRight.setCurrentAndTargetValue(-100.0f);
    rmsOutLevelLeft.setCurrentAndTargetValue(-100.0f);
    rmsOutLevelRight.setCurrentAndTargetValue(-100.0f);

    inputGainModule.prepare(sampleRate, samplesPerBlock, getTotalNumInputChannels());
    outputGainModule.prepare(sampleRate, samplesPerBlock, getTotalNumInputChannels());
    
    for (int slotIdx = 0; slotIdx < 4; slotIdx++){
        
        compressorVector[slotIdx]       ->prepare(sampleRate, samplesPerBlock, getTotalNumInputChannels());
        envelopeFilterVector[slotIdx]   ->prepare(sampleRate, samplesPerBlock, getTotalNumInputChannels());
        reverbVector[slotIdx]           ->prepare(sampleRate, samplesPerBlock, getTotalNumInputChannels());
        distortionVector[slotIdx]       ->prepare(sampleRate, samplesPerBlock, getTotalNumInputChannels());
        
    }
    
    assignActiveModules(ProcessingConstants::Pedals::Identifiers::slot1Param,
                        static_cast<int>(apvts.getParameterAsValue(ProcessingConstants::Pedals::Identifiers::slot1Param).getValue()));
    
    assignActiveModules(ProcessingConstants::Pedals::Identifiers::slot2Param,
                        static_cast<int>(apvts.getParameterAsValue(ProcessingConstants::Pedals::Identifiers::slot2Param).getValue()));
    
    assignActiveModules(ProcessingConstants::Pedals::Identifiers::slot3Param,
                        static_cast<int>(apvts.getParameterAsValue(ProcessingConstants::Pedals::Identifiers::slot3Param).getValue()));
    
    assignActiveModules(ProcessingConstants::Pedals::Identifiers::slot4Param,
                        static_cast<int>(apvts.getParameterAsValue(ProcessingConstants::Pedals::Identifiers::slot4Param).getValue()));

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

void FootprintAudioProcessor::updateRMSLevelMeter(const float decibelValue, juce::LinearSmoothedValue<float>& rmsLevel) {
    if (decibelValue < rmsLevel.getCurrentValue()) rmsLevel.setTargetValue(decibelValue);
    else rmsLevel.setCurrentAndTargetValue(decibelValue);
}

void FootprintAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noInDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    float leftValue, rightValue; // (For RMS)
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    // Input Gain and Waveform visualiser =============================================================================================
    
    inputGainModule.processBlock(buffer, midiMessages);
    guiFifoInput.push(buffer);
    
    // Input RMS ======================================================================================================================
    rmsInLevelLeft.skip(buffer.getNumSamples());
    rmsInLevelRight.skip(buffer.getNumSamples());
    
        // Left Input
    leftValue = juce::Decibels::gainToDecibels(buffer.getRMSLevel(0, 0, buffer.getNumSamples()));
    updateRMSLevelMeter(leftValue, rmsInLevelLeft);
    
        // Right Input
    if (buffer.getNumChannels() > 1) rightValue = juce::Decibels::gainToDecibels(buffer.getRMSLevel(1, 0, buffer.getNumSamples()));
    else rightValue = leftValue;
    updateRMSLevelMeter(rightValue, rmsInLevelRight);


    // DSP Block =======================================================================================================================
    
    activeModules[0]->processBlock(buffer, midiMessages);
    activeModules[1]->processBlock(buffer, midiMessages);
    activeModules[2]->processBlock(buffer, midiMessages);
    activeModules[3]->processBlock(buffer, midiMessages);

    // Output Gain + Mono/Stereo and Waveform Visualiser ===============================================================================
    juce::ScopedNoDenormals noOutDenormals;
    
    bool isStereo = static_cast<bool>(apvts.getRawParameterValue(ProcessingConstants::EditorControls::Identifiers::monoStereoParam)->load());
    if (!isStereo) monoStereoModule.processBlock(buffer, midiMessages);
    
    outputGainModule.processBlock(buffer, midiMessages);
    guiFifoOutput.push(buffer);
    
    // Output RMS ======================================================================================================================
    rmsOutLevelLeft.skip(buffer.getNumSamples());
    rmsOutLevelRight.skip(buffer.getNumSamples());
    
        // Left Input
    leftValue = juce::Decibels::gainToDecibels(buffer.getRMSLevel(0, 0, buffer.getNumSamples()));
    updateRMSLevelMeter(leftValue, rmsOutLevelLeft);
    
        // Right Input
    if (buffer.getNumChannels() > 1) rightValue = juce::Decibels::gainToDecibels(buffer.getRMSLevel(1, 0, buffer.getNumSamples()));
    else rightValue = leftValue;
    updateRMSLevelMeter(rightValue, rmsOutLevelRight);

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
    juce::MemoryOutputStream mos(destData, true);
    apvts.state.writeToStream(mos);

}

void FootprintAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{

    auto tree = juce::ValueTree::readFromData(data, sizeInBytes);
        if (tree.isValid()){
            apvts.replaceState(tree);
            initParameters();
            
            for (int slotIdx = 0; slotIdx < 4; slotIdx++){
                
                compressorVector[slotIdx] = std::make_unique<Compressor>();
                initCompressorParameters(slotIdx);
                
                envelopeFilterVector[slotIdx] = std::make_unique<EnvelopeFilter>();
                initEnvelopeFilterParameters(slotIdx);
                
                reverbVector[slotIdx] = std::make_unique<Reverb>();
                initReverbParameters(slotIdx);
                
                distortionVector[slotIdx] = std::make_unique<Distortion>();
                initDistortionParameters(slotIdx);
                
                audioPassThroughVector[slotIdx] = std::make_unique<AudioPassThrough>();
            }
            
            inputGainModule.setGainValue(inputGain);
            outputGainModule.setGainValue(outputGain);
            
            for (int slotIdx = 0; slotIdx < 4; slotIdx++){
                
                compressorVector[slotIdx] = std::make_unique<Compressor>();
                initCompressorParameters(slotIdx);
                
                envelopeFilterVector[slotIdx] = std::make_unique<EnvelopeFilter>();
                initEnvelopeFilterParameters(slotIdx);
                
                reverbVector[slotIdx] = std::make_unique<Reverb>();
                initReverbParameters(slotIdx);
                
                distortionVector[slotIdx] = std::make_unique<Distortion>();
                initDistortionParameters(slotIdx);
                
                audioPassThroughVector[slotIdx] = std::make_unique<AudioPassThrough>();
            }
            
            apvts.addParameterListener(ProcessingConstants::Pedals::Identifiers::slot1Param, this);
            apvts.addParameterListener(ProcessingConstants::Pedals::Identifiers::slot2Param, this);
            apvts.addParameterListener(ProcessingConstants::Pedals::Identifiers::slot3Param, this);
            apvts.addParameterListener(ProcessingConstants::Pedals::Identifiers::slot4Param, this);
            
        }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FootprintAudioProcessor();
}

void FootprintAudioProcessor::initParameters(){
    
    // Editor Controls
    
    inputGain   = apvts.getRawParameterValue(ProcessingConstants::EditorControls::Identifiers::inputGainParam);
    outputGain  = apvts.getRawParameterValue(ProcessingConstants::EditorControls::Identifiers::outputGainParam);
    
    // Compressor
    attack1     = apvts.getRawParameterValue(ProcessingConstants::Compressor::Identifiers::compressorAttackID1);
    attack2     = apvts.getRawParameterValue(ProcessingConstants::Compressor::Identifiers::compressorAttackID2);
    attack3     = apvts.getRawParameterValue(ProcessingConstants::Compressor::Identifiers::compressorAttackID3);
    attack4     = apvts.getRawParameterValue(ProcessingConstants::Compressor::Identifiers::compressorAttackID4);
    
    release1    = apvts.getRawParameterValue(ProcessingConstants::Compressor::Identifiers::compressorReleaseID1);
    release2    = apvts.getRawParameterValue(ProcessingConstants::Compressor::Identifiers::compressorReleaseID2);
    release3    = apvts.getRawParameterValue(ProcessingConstants::Compressor::Identifiers::compressorReleaseID3);
    release4    = apvts.getRawParameterValue(ProcessingConstants::Compressor::Identifiers::compressorReleaseID4);
    
    threshold1  = apvts.getRawParameterValue(ProcessingConstants::Compressor::Identifiers::compressorThresholdID1);
    threshold2  = apvts.getRawParameterValue(ProcessingConstants::Compressor::Identifiers::compressorThresholdID2);
    threshold3  = apvts.getRawParameterValue(ProcessingConstants::Compressor::Identifiers::compressorThresholdID3);
    threshold4  = apvts.getRawParameterValue(ProcessingConstants::Compressor::Identifiers::compressorThresholdID4);
    
    ratio1      = apvts.getRawParameterValue(ProcessingConstants::Compressor::Identifiers::compressorRatioID1);
    ratio2      = apvts.getRawParameterValue(ProcessingConstants::Compressor::Identifiers::compressorRatioID2);
    ratio3      = apvts.getRawParameterValue(ProcessingConstants::Compressor::Identifiers::compressorRatioID3);
    ratio4      = apvts.getRawParameterValue(ProcessingConstants::Compressor::Identifiers::compressorRatioID4);
    
    compressorBypass1 = apvts.getRawParameterValue(ProcessingConstants::Compressor::Identifiers::compressorBypassedID1);
    compressorBypass2 = apvts.getRawParameterValue(ProcessingConstants::Compressor::Identifiers::compressorBypassedID2);
    compressorBypass3 = apvts.getRawParameterValue(ProcessingConstants::Compressor::Identifiers::compressorBypassedID3);
    compressorBypass4 = apvts.getRawParameterValue(ProcessingConstants::Compressor::Identifiers::compressorBypassedID4);
    
    // Reverb
    wetDryMix1      = apvts.getRawParameterValue(ProcessingConstants::Reverb::Identifiers::reverbWetMixID1);
    wetDryMix2      = apvts.getRawParameterValue(ProcessingConstants::Reverb::Identifiers::reverbWetMixID2);
    wetDryMix3      = apvts.getRawParameterValue(ProcessingConstants::Reverb::Identifiers::reverbWetMixID3);
    wetDryMix4      = apvts.getRawParameterValue(ProcessingConstants::Reverb::Identifiers::reverbWetMixID4);
    
    reverbBypass1   = apvts.getRawParameterValue(ProcessingConstants::Reverb::Identifiers::reverbBypassedID1);
    reverbBypass2   = apvts.getRawParameterValue(ProcessingConstants::Reverb::Identifiers::reverbBypassedID2);
    reverbBypass3   = apvts.getRawParameterValue(ProcessingConstants::Reverb::Identifiers::reverbBypassedID3);
    reverbBypass4   = apvts.getRawParameterValue(ProcessingConstants::Reverb::Identifiers::reverbBypassedID4);
    
    reverbIRChoice1 = apvts.getRawParameterValue(ProcessingConstants::Reverb::Identifiers::reverbIRChoiceID1);
    reverbIRChoice2 = apvts.getRawParameterValue(ProcessingConstants::Reverb::Identifiers::reverbIRChoiceID2);
    reverbIRChoice3 = apvts.getRawParameterValue(ProcessingConstants::Reverb::Identifiers::reverbIRChoiceID3);
    reverbIRChoice4 = apvts.getRawParameterValue(ProcessingConstants::Reverb::Identifiers::reverbIRChoiceID4);
    
    // Distortion
    distGain1   = apvts.getRawParameterValue(ProcessingConstants::Distortion::Identifiers::distortionGainID1);
    distGain2   = apvts.getRawParameterValue(ProcessingConstants::Distortion::Identifiers::distortionGainID2);
    distGain3   = apvts.getRawParameterValue(ProcessingConstants::Distortion::Identifiers::distortionGainID3);
    distGain4   = apvts.getRawParameterValue(ProcessingConstants::Distortion::Identifiers::distortionGainID4);
    
    level1      = apvts.getRawParameterValue(ProcessingConstants::Distortion::Identifiers::distortionLevelID1);
    level2      = apvts.getRawParameterValue(ProcessingConstants::Distortion::Identifiers::distortionLevelID2);
    level3      = apvts.getRawParameterValue(ProcessingConstants::Distortion::Identifiers::distortionLevelID3);
    level4      = apvts.getRawParameterValue(ProcessingConstants::Distortion::Identifiers::distortionLevelID4);
    
    tone1       = apvts.getRawParameterValue(ProcessingConstants::Distortion::Identifiers::distortionToneID1);
    tone2       = apvts.getRawParameterValue(ProcessingConstants::Distortion::Identifiers::distortionToneID2);
    tone3       = apvts.getRawParameterValue(ProcessingConstants::Distortion::Identifiers::distortionToneID3);
    tone4       = apvts.getRawParameterValue(ProcessingConstants::Distortion::Identifiers::distortionToneID4);
    
    distortionBypass1 = apvts.getRawParameterValue(ProcessingConstants::Distortion::Identifiers::distortionBypassedID1);
    distortionBypass2 = apvts.getRawParameterValue(ProcessingConstants::Distortion::Identifiers::distortionBypassedID2);
    distortionBypass3 = apvts.getRawParameterValue(ProcessingConstants::Distortion::Identifiers::distortionBypassedID3);
    distortionBypass4 = apvts.getRawParameterValue(ProcessingConstants::Distortion::Identifiers::distortionBypassedID4);
    
    
    // Envelope Filter
    quality1            = apvts.getRawParameterValue(ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterQualityID1);
    quality2            = apvts.getRawParameterValue(ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterQualityID2);
    quality3            = apvts.getRawParameterValue(ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterQualityID3);
    quality4            = apvts.getRawParameterValue(ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterQualityID4);
    
    sensitivity1        = apvts.getRawParameterValue(ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterSensitivityID1);
    sensitivity2        = apvts.getRawParameterValue(ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterSensitivityID2);
    sensitivity3        = apvts.getRawParameterValue(ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterSensitivityID3);
    sensitivity4        = apvts.getRawParameterValue(ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterSensitivityID4);
    
    cutoffThreshold1    = apvts.getRawParameterValue(ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterCutoffThresholdID1);
    cutoffThreshold2    = apvts.getRawParameterValue(ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterCutoffThresholdID2);
    cutoffThreshold3    = apvts.getRawParameterValue(ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterCutoffThresholdID3);
    cutoffThreshold4    = apvts.getRawParameterValue(ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterCutoffThresholdID4);
    
    envelopeFilterBypass1 = apvts.getRawParameterValue(ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterBypassedID1);
    envelopeFilterBypass2 = apvts.getRawParameterValue(ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterBypassedID2);
    envelopeFilterBypass3 = apvts.getRawParameterValue(ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterBypassedID3);
    envelopeFilterBypass4 = apvts.getRawParameterValue(ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterBypassedID4);
    
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

void FootprintAudioProcessor::initCompressorParameters(const int &slotIdx){
    
    switch (slotIdx) {
        
        case 0: {
            
            compressorVector[slotIdx]->setAttack(attack1);
            compressorVector[slotIdx]->setRelease(release1);
            compressorVector[slotIdx]->setThreshold(threshold1);
            compressorVector[slotIdx]->setRatio(ratio1);
            compressorVector[slotIdx]->setBypassParam(compressorBypass1);
        }
            break;
            
        case 1: {
            
            compressorVector[slotIdx]->setAttack(attack2);
            compressorVector[slotIdx]->setRelease(release2);
            compressorVector[slotIdx]->setThreshold(threshold2);
            compressorVector[slotIdx]->setRatio(ratio2);
            compressorVector[slotIdx]->setBypassParam(compressorBypass2);
        }
            break;
            
        case 2: {
            
            compressorVector[slotIdx]->setAttack(attack3);
            compressorVector[slotIdx]->setRelease(release3);
            compressorVector[slotIdx]->setThreshold(threshold3);
            compressorVector[slotIdx]->setRatio(ratio3);
            compressorVector[slotIdx]->setBypassParam(compressorBypass3);
        }
            break;
        
        case 3:{
            
            compressorVector[slotIdx]->setAttack(attack4);
            compressorVector[slotIdx]->setRelease(release4);
            compressorVector[slotIdx]->setThreshold(threshold4);
            compressorVector[slotIdx]->setRatio(ratio4);
            compressorVector[slotIdx]->setBypassParam(compressorBypass4);
        }
            break;
    }
}

void FootprintAudioProcessor::initEnvelopeFilterParameters(const int &slotIdx){
    
    switch (slotIdx) {
        
        case 0: {
            
            envelopeFilterVector[slotIdx]->setQualityFactor(quality1);
            envelopeFilterVector[slotIdx]->setMinCutoffFreq(cutoffThreshold1);
            envelopeFilterVector[slotIdx]->setSensitivity(sensitivity1);
            envelopeFilterVector[slotIdx]->setBypassParam(envelopeFilterBypass1);
        }
            break;
            
        case 1: {
            
            envelopeFilterVector[slotIdx]->setQualityFactor(quality2);
            envelopeFilterVector[slotIdx]->setMinCutoffFreq(cutoffThreshold2);
            envelopeFilterVector[slotIdx]->setSensitivity(sensitivity2);
            envelopeFilterVector[slotIdx]->setBypassParam(envelopeFilterBypass2);
        }
            break;
            
        case 2: {
            
            envelopeFilterVector[slotIdx]->setQualityFactor(quality3);
            envelopeFilterVector[slotIdx]->setMinCutoffFreq(cutoffThreshold3);
            envelopeFilterVector[slotIdx]->setSensitivity(sensitivity3);
            envelopeFilterVector[slotIdx]->setBypassParam(envelopeFilterBypass3);
        }
            break;
        
        case 3:{
            
            envelopeFilterVector[slotIdx]->setQualityFactor(quality4);
            envelopeFilterVector[slotIdx]->setMinCutoffFreq(cutoffThreshold4);
            envelopeFilterVector[slotIdx]->setSensitivity(sensitivity4);
            envelopeFilterVector[slotIdx]->setBypassParam(envelopeFilterBypass4);
        }
            break;
    }
    
}

void FootprintAudioProcessor::initDistortionParameters(const int &slotIdx){
    
    switch (slotIdx) {
        
        case 0: {
            
            distortionVector[slotIdx]->setGain(distGain1);
            distortionVector[slotIdx]->setLevel(level1);
            distortionVector[slotIdx]->setTone(tone1);
            distortionVector[slotIdx]->setBypassParam(distortionBypass1);
        }
            break;
            
        case 1: {
            
            distortionVector[slotIdx]->setGain(distGain2);
            distortionVector[slotIdx]->setLevel(level2);
            distortionVector[slotIdx]->setTone(tone2);
            distortionVector[slotIdx]->setBypassParam(distortionBypass2);
        }
            break;
            
        case 2: {
            
            distortionVector[slotIdx]->setGain(distGain3);
            distortionVector[slotIdx]->setLevel(level3);
            distortionVector[slotIdx]->setTone(tone3);
            distortionVector[slotIdx]->setBypassParam(distortionBypass3);
        }
            break;
        
        case 3:{
            
            distortionVector[slotIdx]->setGain(distGain4);
            distortionVector[slotIdx]->setLevel(level4);
            distortionVector[slotIdx]->setTone(tone4);
            distortionVector[slotIdx]->setBypassParam(distortionBypass4);
        }
            break;
    }
}

void FootprintAudioProcessor::initReverbParameters(const int &slotIdx){
    
    switch (slotIdx) {
        
        case 0: {
            
            reverbVector[slotIdx]->setWet(wetDryMix1);
            reverbVector[slotIdx]->setBypassParam(reverbBypass1);
            reverbVector[slotIdx]->setIRChoiceParameter(reverbIRChoice1);
        }
            break;
            
        case 1: {
            
            reverbVector[slotIdx]->setWet(wetDryMix2);
            reverbVector[slotIdx]->setBypassParam(reverbBypass2);
            reverbVector[slotIdx]->setIRChoiceParameter(reverbIRChoice2);
        }
            break;
            
        case 2: {
            
            reverbVector[slotIdx]->setWet(wetDryMix3);
            reverbVector[slotIdx]->setBypassParam(reverbBypass3);
            reverbVector[slotIdx]->setIRChoiceParameter(reverbIRChoice3);
        }
            break;
        
        case 3:{
            
            reverbVector[slotIdx]->setWet(wetDryMix4);
            reverbVector[slotIdx]->setBypassParam(reverbBypass4);
            reverbVector[slotIdx]->setIRChoiceParameter(reverbIRChoice4);
        }
            break;
    }
}

void FootprintAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue){
    
    int newValueInt         = static_cast<int>(newValue);
    assignActiveModules(parameterID, newValueInt);
}

void FootprintAudioProcessor::assignActiveModules(const juce::String &paramID, int value) {
    
    if (paramID == static_cast<juce::String>(ProcessingConstants::Pedals::Identifiers::slot1Param)) {
        
        switch (value) {
            case 0: {
                //DBG("Assigning Audio Pass though to slot 1");
                activeModules[0] = audioPassThroughVector[0].get();
                break;
            }
            
            case 1: {
                //DBG("Assigning Compressor to slot 1");
                activeModules[0] = compressorVector[0].get();
                break;
            }
                
            case 2: {
                //DBG("Assigning distortion to slot 1");
                activeModules[0] = distortionVector[0].get();
                break;
            }
                
            case 3: {
                //DBG("Assigning envelope Filter to slot 1");
                activeModules[0] = envelopeFilterVector[0].get();
                break;
            }
            
            case 4: {
                //DBG("Assigning reverb to slot 1");
                activeModules[0] = reverbVector[0].get();
                break;
            }
        }
    }
    
    else if (paramID == static_cast<juce::String>(ProcessingConstants::Pedals::Identifiers::slot2Param)) {
        
        switch (value) {
            case 0: {
                //DBG("Assigning Audio Pass though to slot 2");
                activeModules[1] = audioPassThroughVector[1].get();
                break;
            }
            
            case 1: {
                //DBG("Assigning compressor to slot 2");
                activeModules[1] = compressorVector[1].get();
                break;
            }
                
            case 2: {
                //DBG("Assigning distortion to slot 2");
                activeModules[1] = distortionVector[1].get();
                break;
            }
                
            case 3: {
                //DBG("Assigning envelope to slot 2");
                activeModules[1] = envelopeFilterVector[1].get();
                break;
            }
            
            case 4: {
                //DBG("Assigning reverb though to slot 2");
                activeModules[1] = reverbVector[1].get();
                break;
            }
        }
        
        
    }
    
    else if (paramID == static_cast<juce::String>(ProcessingConstants::Pedals::Identifiers::slot3Param)) {
        
        switch (value) {
            case 0: {
                //DBG("Assigning Audio Pass though to slot 3");
                activeModules[2] = audioPassThroughVector[2].get();
                break;
            }
            
            case 1: {
                //DBG("Assigning compressor to slot 3");
                activeModules[2] = compressorVector[2].get();
                break;
            }
                
            case 2: {
                //DBG("Assigning distortion to slot 3");
                activeModules[2] = distortionVector[2].get();
                break;
            }
                
            case 3: {
                //DBG("Assigning envelope to slot 3");
                activeModules[2] = envelopeFilterVector[2].get();
                break;
            }
            
            case 4: {
                //DBG("Assigning reverb though to slot 2");
                activeModules[2] = reverbVector[2].get();
                break;
            }
        }
    }
    
    else if (paramID == static_cast<juce::String>(ProcessingConstants::Pedals::Identifiers::slot4Param)) {
        
        switch (value) {
            case 0: {
                //DBG("Assigning Audio Pass though to slot 4");
                activeModules[3] = audioPassThroughVector[3].get();
                break;
            }
            case 1: {
                //DBG("Assigning compressor to slot 4");
                activeModules[3] = compressorVector[3].get();
                break;
            }
                
            case 2: {
                //DBG("Assigning distortion to slot 4");
                activeModules[3] = distortionVector[3].get();
                break;
            }
                
            case 3: {
                //DBG("Assigning envelope to slot 4");
                activeModules[3] = envelopeFilterVector[3].get();
                break;
            }
            
            case 4: {
                //DBG("Assigning reverb to slot 4");
                activeModules[3] = reverbVector[3].get();
                break;
            }
        }
    }    
}
