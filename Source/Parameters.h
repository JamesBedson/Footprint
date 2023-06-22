/*
  ==============================================================================

    Parametres.h
    Created: 23 May 2023 5:44:28pm
    Author:  James Bedson

  ==============================================================================
*/

#pragma once
{
    
    // Editor
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::EditorControls::Identifiers::inputGainParam, 1},
                                                ProcessingConstants::EditorControls::Identifiers::inputGainID,
                                                juce::NormalisableRange<float>(ProcessingConstants::EditorControls::Numeric::inputGainMin,
                                                                               ProcessingConstants::EditorControls::Numeric::inputGainMax,
                                                                               ProcessingConstants::EditorControls::Numeric::inputGainIncrement,
                                                                               ProcessingConstants::EditorControls::Numeric::inputGainSkew),
                                                ProcessingConstants::EditorControls::Numeric::defaultInputGain),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::EditorControls::Identifiers::outputGainParam, 1},
                                                ProcessingConstants::EditorControls::Identifiers::outputGainID,
                                                juce::NormalisableRange<float>(ProcessingConstants::EditorControls::Numeric::outputGainMin,
                                                                               ProcessingConstants::EditorControls::Numeric::outputGainMax,
                                                                               ProcessingConstants::EditorControls::Numeric::outputGainIncrement,
                                                                               ProcessingConstants::EditorControls::Numeric::outputGainSkew),
                                                ProcessingConstants::EditorControls::Numeric::defaultOutputGain),
    
    std::make_unique<juce::AudioParameterBool>(juce::ParameterID {ProcessingConstants::EditorControls::Identifiers::monoStereoParam, 1},
                                               ProcessingConstants::EditorControls::Identifiers::monoStereoID,
                                               ProcessingConstants::EditorControls::Numeric::isStereo),
    
    // Pedal Slots
    
    std::make_unique<NonAutomatableParameterChoice>(juce::ParameterID {ProcessingConstants::Pedals::Identifiers::slot1Param, 2},
                                                 ProcessingConstants::Pedals::Identifiers::slot1ID,
                                                 ProcessingConstants::Pedals::Choices::choiceArray,
                                                 0),
    
    std::make_unique<NonAutomatableParameterChoice>(juce::ParameterID {ProcessingConstants::Pedals::Identifiers::slot2Param, 2},
                                                 ProcessingConstants::Pedals::Identifiers::slot2ID,
                                                 ProcessingConstants::Pedals::Choices::choiceArray,
                                                 0),
    
    std::make_unique<NonAutomatableParameterChoice>(juce::ParameterID {ProcessingConstants::Pedals::Identifiers::slot3Param, 2},
                                                 ProcessingConstants::Pedals::Identifiers::slot3ID,
                                                 ProcessingConstants::Pedals::Choices::choiceArray,
                                                 0),
    
    std::make_unique<NonAutomatableParameterChoice>(juce::ParameterID {ProcessingConstants::Pedals::Identifiers::slot4Param, 2},
                                                 ProcessingConstants::Pedals::Identifiers::slot4ID,
                                                 ProcessingConstants::Pedals::Choices::choiceArray,
                                                 0),
    
    // Compressor
    // ================================================================================================================================
    
        // Attack
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorAttackID1, 3},
                                                ProcessingConstants::Compressor::Identifiers::compressorAttackName1,
                                                juce::NormalisableRange<float>(ProcessingConstants::Compressor::Numeric::attackMin,
                                                                               ProcessingConstants::Compressor::Numeric::attackMax,
                                                                               ProcessingConstants::Compressor::Numeric::attackIncrement,
                                                                               ProcessingConstants::Compressor::Numeric::attackSkew),
                                                ProcessingConstants::Compressor::Numeric::defaultAttack),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorAttackID2, 3},
                                                ProcessingConstants::Compressor::Identifiers::compressorAttackName2,
                                                juce::NormalisableRange<float>(ProcessingConstants::Compressor::Numeric::attackMin,
                                                                               ProcessingConstants::Compressor::Numeric::attackMax,
                                                                               ProcessingConstants::Compressor::Numeric::attackIncrement,
                                                                               ProcessingConstants::Compressor::Numeric::attackSkew),
                                                ProcessingConstants::Compressor::Numeric::defaultAttack),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorAttackID3, 3},
                                                ProcessingConstants::Compressor::Identifiers::compressorAttackName3,
                                                juce::NormalisableRange<float>(ProcessingConstants::Compressor::Numeric::attackMin,
                                                                               ProcessingConstants::Compressor::Numeric::attackMax,
                                                                               ProcessingConstants::Compressor::Numeric::attackIncrement,
                                                                               ProcessingConstants::Compressor::Numeric::attackSkew),
                                                ProcessingConstants::Compressor::Numeric::defaultAttack),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorAttackID4, 3},
                                                ProcessingConstants::Compressor::Identifiers::compressorAttackName4,
                                                juce::NormalisableRange<float>(ProcessingConstants::Compressor::Numeric::attackMin,
                                                                               ProcessingConstants::Compressor::Numeric::attackMax,
                                                                               ProcessingConstants::Compressor::Numeric::attackIncrement,
                                                                               ProcessingConstants::Compressor::Numeric::attackSkew),
                                                ProcessingConstants::Compressor::Numeric::defaultAttack),
        // Release
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorReleaseID1, 3},
                                                ProcessingConstants::Compressor::Identifiers::compressotReleaseName1,
                                                juce::NormalisableRange<float>(ProcessingConstants::Compressor::Numeric::releaseMin,
                                                                               ProcessingConstants::Compressor::Numeric::releaseMax,
                                                                               ProcessingConstants::Compressor::Numeric::releaseIncrement,
                                                                               ProcessingConstants::Compressor::Numeric::releaseSkew),
                                                ProcessingConstants::Compressor::Numeric::defaultRelease),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorReleaseID2, 3},
                                                ProcessingConstants::Compressor::Identifiers::compressotReleaseName2,
                                                juce::NormalisableRange<float>(ProcessingConstants::Compressor::Numeric::releaseMin,
                                                                               ProcessingConstants::Compressor::Numeric::releaseMax,
                                                                               ProcessingConstants::Compressor::Numeric::releaseIncrement,
                                                                               ProcessingConstants::Compressor::Numeric::releaseSkew),
                                                ProcessingConstants::Compressor::Numeric::defaultRelease),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorReleaseID3, 3},
                                                ProcessingConstants::Compressor::Identifiers::compressotReleaseName3,
                                                juce::NormalisableRange<float>(ProcessingConstants::Compressor::Numeric::releaseMin,
                                                                               ProcessingConstants::Compressor::Numeric::releaseMax,
                                                                               ProcessingConstants::Compressor::Numeric::releaseIncrement,
                                                                               ProcessingConstants::Compressor::Numeric::releaseSkew),
                                                ProcessingConstants::Compressor::Numeric::defaultRelease),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorReleaseID4, 3},
                                                ProcessingConstants::Compressor::Identifiers::compressotReleaseName4,
                                                juce::NormalisableRange<float>(ProcessingConstants::Compressor::Numeric::releaseMin,
                                                                               ProcessingConstants::Compressor::Numeric::releaseMax,
                                                                               ProcessingConstants::Compressor::Numeric::releaseIncrement,
                                                                               ProcessingConstants::Compressor::Numeric::releaseSkew),
                                                ProcessingConstants::Compressor::Numeric::defaultRelease),
    
        // Threshold
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorThresholdID1, 3},
                                                ProcessingConstants::Compressor::Identifiers::compressorThresholdName1,
                                                juce::NormalisableRange<float>(ProcessingConstants::Compressor::Numeric::thresholdMin,
                                                                               ProcessingConstants::Compressor::Numeric::thresholdMax,
                                                                               ProcessingConstants::Compressor::Numeric::thresholdIncrement,
                                                                               ProcessingConstants::Compressor::Numeric::thresholdSkew),
                                                ProcessingConstants::Compressor::Numeric::defaultThreshold),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorThresholdID2, 3},
                                                ProcessingConstants::Compressor::Identifiers::compressorThresholdName2,
                                                juce::NormalisableRange<float>(ProcessingConstants::Compressor::Numeric::thresholdMin,
                                                                               ProcessingConstants::Compressor::Numeric::thresholdMax,
                                                                               ProcessingConstants::Compressor::Numeric::thresholdIncrement,
                                                                               ProcessingConstants::Compressor::Numeric::thresholdSkew),
                                                ProcessingConstants::Compressor::Numeric::defaultThreshold),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorThresholdID3, 3},
                                                ProcessingConstants::Compressor::Identifiers::compressorThresholdName3,
                                                juce::NormalisableRange<float>(ProcessingConstants::Compressor::Numeric::thresholdMin,
                                                                               ProcessingConstants::Compressor::Numeric::thresholdMax,
                                                                               ProcessingConstants::Compressor::Numeric::thresholdIncrement,
                                                                               ProcessingConstants::Compressor::Numeric::thresholdSkew),
                                                ProcessingConstants::Compressor::Numeric::defaultThreshold),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorThresholdID4, 3},
                                                ProcessingConstants::Compressor::Identifiers::compressorThresholdName4,
                                                juce::NormalisableRange<float>(ProcessingConstants::Compressor::Numeric::thresholdMin,
                                                                               ProcessingConstants::Compressor::Numeric::thresholdMax,
                                                                               ProcessingConstants::Compressor::Numeric::thresholdIncrement,
                                                                               ProcessingConstants::Compressor::Numeric::thresholdSkew),
                                                ProcessingConstants::Compressor::Numeric::defaultThreshold),
    
        // Ratio
    
    std::make_unique<juce::AudioParameterInt>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorRatioID1, 3},
                                              ProcessingConstants::Compressor::Identifiers::compressorRatioName1,
                                              ProcessingConstants::Compressor::Numeric::ratioMin,
                                              ProcessingConstants::Compressor::Numeric::ratioMax,
                                              ProcessingConstants::Compressor::Numeric::defaultRatio),
    
    std::make_unique<juce::AudioParameterInt>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorRatioID2, 3},
                                              ProcessingConstants::Compressor::Identifiers::compressorRatioName2,
                                              ProcessingConstants::Compressor::Numeric::ratioMin,
                                              ProcessingConstants::Compressor::Numeric::ratioMax,
                                              ProcessingConstants::Compressor::Numeric::defaultRatio),
    
    std::make_unique<juce::AudioParameterInt>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorRatioID3, 3},
                                              ProcessingConstants::Compressor::Identifiers::compressorRatioName3,
                                              ProcessingConstants::Compressor::Numeric::ratioMin,
                                              ProcessingConstants::Compressor::Numeric::ratioMax,
                                              ProcessingConstants::Compressor::Numeric::defaultRatio),
    
    std::make_unique<juce::AudioParameterInt>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorRatioID4, 3},
                                              ProcessingConstants::Compressor::Identifiers::compressorRatioName4,
                                              ProcessingConstants::Compressor::Numeric::ratioMin,
                                              ProcessingConstants::Compressor::Numeric::ratioMax,
                                              ProcessingConstants::Compressor::Numeric::defaultRatio),
    
        // Bypass
    std::make_unique<juce::AudioParameterBool>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorBypassedID1, 3},
                                               ProcessingConstants::Compressor::Identifiers::compressorBypassName1, false),
    
    std::make_unique<juce::AudioParameterBool>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorBypassedID2, 3},
                                               ProcessingConstants::Compressor::Identifiers::compressorBypassName2, false),
    
    std::make_unique<juce::AudioParameterBool>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorBypassedID3, 3},
                                               ProcessingConstants::Compressor::Identifiers::compressorBypassName3, false),
    
    std::make_unique<juce::AudioParameterBool>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorBypassedID4, 3},
                                               ProcessingConstants::Compressor::Identifiers::compressorBypassName4, false),

    
    // Reverb
    // ================================================================================================================================
    
        // Wet/Dry
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Reverb::Identifiers::reverbWetMixID1, 4},
                                                ProcessingConstants::Reverb::Identifiers::reverbWetMixName1,
                                                juce::NormalisableRange<float>(ProcessingConstants::Reverb::Numeric::wetMin,
                                                                               ProcessingConstants::Reverb::Numeric::wetMax,
                                                                               ProcessingConstants::Reverb::Numeric::wetIncrement,
                                                                               ProcessingConstants::Reverb::Numeric::wetSkew),
                                                ProcessingConstants::Reverb::Numeric::defaultWetMix),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Reverb::Identifiers::reverbWetMixID2, 4},
                                                ProcessingConstants::Reverb::Identifiers::reverbWetMixName2,
                                                juce::NormalisableRange<float>(ProcessingConstants::Reverb::Numeric::wetMin,
                                                                               ProcessingConstants::Reverb::Numeric::wetMax,
                                                                               ProcessingConstants::Reverb::Numeric::wetIncrement,
                                                                               ProcessingConstants::Reverb::Numeric::wetSkew),
                                                ProcessingConstants::Reverb::Numeric::defaultWetMix),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Reverb::Identifiers::reverbWetMixID3, 4},
                                                ProcessingConstants::Reverb::Identifiers::reverbWetMixName3,
                                                juce::NormalisableRange<float>(ProcessingConstants::Reverb::Numeric::wetMin,
                                                                               ProcessingConstants::Reverb::Numeric::wetMax,
                                                                               ProcessingConstants::Reverb::Numeric::wetIncrement,
                                                                               ProcessingConstants::Reverb::Numeric::wetSkew),
                                                ProcessingConstants::Reverb::Numeric::defaultWetMix),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Reverb::Identifiers::reverbWetMixID4, 4},
                                                ProcessingConstants::Reverb::Identifiers::reverbWetMixName4,
                                                juce::NormalisableRange<float>(ProcessingConstants::Reverb::Numeric::wetMin,
                                                                               ProcessingConstants::Reverb::Numeric::wetMax,
                                                                               ProcessingConstants::Reverb::Numeric::wetIncrement,
                                                                               ProcessingConstants::Reverb::Numeric::wetSkew),
                                                ProcessingConstants::Reverb::Numeric::defaultWetMix),
    
    // Impulse Response Choice
    
    std::make_unique<juce::AudioParameterChoice>(juce::ParameterID {ProcessingConstants::Reverb::Identifiers::reverbIRChoiceID1, 4},
                                                 ProcessingConstants::Reverb::Identifiers::reverbIRChoiceName1,
                                                 ProcessingConstants::Reverb::IRChoices::irChoiceArray,
                                                 ProcessingConstants::Reverb::Numeric::defaultIRChoice),
    
    std::make_unique<juce::AudioParameterChoice>(juce::ParameterID {ProcessingConstants::Reverb::Identifiers::reverbIRChoiceID2, 4},
                                                 ProcessingConstants::Reverb::Identifiers::reverbIRChoiceName2,
                                                 ProcessingConstants::Reverb::IRChoices::irChoiceArray,
                                                 ProcessingConstants::Reverb::Numeric::defaultIRChoice),
    
    std::make_unique<juce::AudioParameterChoice>(juce::ParameterID {ProcessingConstants::Reverb::Identifiers::reverbIRChoiceID3, 4},
                                                 ProcessingConstants::Reverb::Identifiers::reverbIRChoiceName3,
                                                 ProcessingConstants::Reverb::IRChoices::irChoiceArray,
                                                 ProcessingConstants::Reverb::Numeric::defaultIRChoice),
    
    std::make_unique<juce::AudioParameterChoice>(juce::ParameterID {ProcessingConstants::Reverb::Identifiers::reverbIRChoiceID4, 4},
                                                 ProcessingConstants::Reverb::Identifiers::reverbIRChoiceName4,
                                                 ProcessingConstants::Reverb::IRChoices::irChoiceArray,
                                                 ProcessingConstants::Reverb::Numeric::defaultIRChoice),
    
    
        // Bypass
    std::make_unique<juce::AudioParameterBool>(juce::ParameterID {ProcessingConstants::Reverb::Identifiers::reverbBypassedID1, 4},
                                               ProcessingConstants::Reverb::Identifiers::reverbBypassName1, false),
    
    std::make_unique<juce::AudioParameterBool>(juce::ParameterID {ProcessingConstants::Reverb::Identifiers::reverbBypassedID2, 4},
                                               ProcessingConstants::Reverb::Identifiers::reverbBypassName2, false),
    
    std::make_unique<juce::AudioParameterBool>(juce::ParameterID {ProcessingConstants::Reverb::Identifiers::reverbBypassedID3, 4},
                                               ProcessingConstants::Reverb::Identifiers::reverbBypassName3, false),
    
    std::make_unique<juce::AudioParameterBool>(juce::ParameterID {ProcessingConstants::Reverb::Identifiers::reverbBypassedID4, 4},
                                               ProcessingConstants::Reverb::Identifiers::reverbBypassName4, false),
    
    
    
    // Distortion
    // ================================================================================================================================
    
        // Gain
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Distortion::Identifiers::distortionGainID1, 5},
                                                ProcessingConstants::Distortion::Identifiers::distortionGainName1,
                                                juce::NormalisableRange<float>(ProcessingConstants::Distortion::Numeric::minGainDecibels,
                                                                               ProcessingConstants::Distortion::Numeric::maxGainDecibels,
                                                                               ProcessingConstants::Distortion::Numeric::gainIncrement,
                                                                               ProcessingConstants::Distortion::Numeric::gainskew),
                                                ProcessingConstants::Distortion::Numeric::defaultGainDecibels),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Distortion::Identifiers::distortionGainID2, 5},
                                                ProcessingConstants::Distortion::Identifiers::distortionGainName2,
                                                juce::NormalisableRange<float>(ProcessingConstants::Distortion::Numeric::minGainDecibels,
                                                                               ProcessingConstants::Distortion::Numeric::maxGainDecibels,
                                                                               ProcessingConstants::Distortion::Numeric::gainIncrement,
                                                                               ProcessingConstants::Distortion::Numeric::gainskew),
                                                ProcessingConstants::Distortion::Numeric::defaultGainDecibels),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Distortion::Identifiers::distortionGainID3, 5},
                                                ProcessingConstants::Distortion::Identifiers::distortionGainName3,
                                                juce::NormalisableRange<float>(ProcessingConstants::Distortion::Numeric::minGainDecibels,
                                                                               ProcessingConstants::Distortion::Numeric::maxGainDecibels,
                                                                               ProcessingConstants::Distortion::Numeric::gainIncrement,
                                                                               ProcessingConstants::Distortion::Numeric::gainskew),
                                                ProcessingConstants::Distortion::Numeric::defaultGainDecibels),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Distortion::Identifiers::distortionGainID4, 5},
                                                ProcessingConstants::Distortion::Identifiers::distortionGainName4,
                                                juce::NormalisableRange<float>(ProcessingConstants::Distortion::Numeric::minGainDecibels,
                                                                               ProcessingConstants::Distortion::Numeric::maxGainDecibels,
                                                                               ProcessingConstants::Distortion::Numeric::gainIncrement,
                                                                               ProcessingConstants::Distortion::Numeric::gainskew),
                                                ProcessingConstants::Distortion::Numeric::defaultGainDecibels),
    
    
        // Level
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Distortion::Identifiers::distortionLevelID1, 5},
                                                ProcessingConstants::Distortion::Identifiers::distortionLevelName1,
                                                juce::NormalisableRange<float>(ProcessingConstants::Distortion::Numeric::minLevel,
                                                                               ProcessingConstants::Distortion::Numeric::maxLevel,
                                                                               ProcessingConstants::Distortion::Numeric::levelIncrement,
                                                                               ProcessingConstants::Distortion::Numeric::levelSkew),
                                                ProcessingConstants::Distortion::Numeric::defaultLevel),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Distortion::Identifiers::distortionLevelID2, 5},
                                                ProcessingConstants::Distortion::Identifiers::distortionLevelName2,
                                                juce::NormalisableRange<float>(ProcessingConstants::Distortion::Numeric::minLevel,
                                                                               ProcessingConstants::Distortion::Numeric::maxLevel,
                                                                               ProcessingConstants::Distortion::Numeric::levelIncrement,
                                                                               ProcessingConstants::Distortion::Numeric::levelSkew),
                                                ProcessingConstants::Distortion::Numeric::defaultLevel),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Distortion::Identifiers::distortionLevelID3, 5},
                                                ProcessingConstants::Distortion::Identifiers::distortionLevelName3,
                                                juce::NormalisableRange<float>(ProcessingConstants::Distortion::Numeric::minLevel,
                                                                               ProcessingConstants::Distortion::Numeric::maxLevel,
                                                                               ProcessingConstants::Distortion::Numeric::levelIncrement,
                                                                               ProcessingConstants::Distortion::Numeric::levelSkew),
                                                ProcessingConstants::Distortion::Numeric::defaultLevel),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Distortion::Identifiers::distortionLevelID4, 5},
                                                ProcessingConstants::Distortion::Identifiers::distortionLevelName4,
                                                juce::NormalisableRange<float>(ProcessingConstants::Distortion::Numeric::minLevel,
                                                                               ProcessingConstants::Distortion::Numeric::maxLevel,
                                                                               ProcessingConstants::Distortion::Numeric::levelIncrement,
                                                                               ProcessingConstants::Distortion::Numeric::levelSkew),
                                                ProcessingConstants::Distortion::Numeric::defaultLevel),
    
    
        // Tone
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Distortion::Identifiers::distortionToneID1, 5},
                                                ProcessingConstants::Distortion::Identifiers::distortionToneName1,
                                                juce::NormalisableRange<float>(ProcessingConstants::Distortion::Numeric::minTone,
                                                                               ProcessingConstants::Distortion::Numeric::maxTone,
                                                                               ProcessingConstants::Distortion::Numeric::toneIncrement,
                                                                               ProcessingConstants::Distortion::Numeric::toneSkew),
                                                ProcessingConstants::Distortion::Numeric::defaultTone),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Distortion::Identifiers::distortionToneID2, 5},
                                                ProcessingConstants::Distortion::Identifiers::distortionToneName2,
                                                juce::NormalisableRange<float>(ProcessingConstants::Distortion::Numeric::minTone,
                                                                               ProcessingConstants::Distortion::Numeric::maxTone,
                                                                               ProcessingConstants::Distortion::Numeric::toneIncrement,
                                                                               ProcessingConstants::Distortion::Numeric::toneSkew),
                                                ProcessingConstants::Distortion::Numeric::defaultTone),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Distortion::Identifiers::distortionToneID3, 5},
                                                ProcessingConstants::Distortion::Identifiers::distortionToneName3,
                                                juce::NormalisableRange<float>(ProcessingConstants::Distortion::Numeric::minTone,
                                                                               ProcessingConstants::Distortion::Numeric::maxTone,
                                                                               ProcessingConstants::Distortion::Numeric::toneIncrement,
                                                                               ProcessingConstants::Distortion::Numeric::toneSkew),
                                                ProcessingConstants::Distortion::Numeric::defaultTone),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Distortion::Identifiers::distortionToneID4, 5},
                                                ProcessingConstants::Distortion::Identifiers::distortionToneName4,
                                                juce::NormalisableRange<float>(ProcessingConstants::Distortion::Numeric::minTone,
                                                                               ProcessingConstants::Distortion::Numeric::maxTone,
                                                                               ProcessingConstants::Distortion::Numeric::toneIncrement,
                                                                               ProcessingConstants::Distortion::Numeric::toneSkew),
                                                ProcessingConstants::Distortion::Numeric::defaultTone),
    
        // Bypass
    
    std::make_unique<juce::AudioParameterBool>(juce::ParameterID {ProcessingConstants::Distortion::Identifiers::distortionBypassedID1, 5},
                                               ProcessingConstants::Distortion::Identifiers::distortionBypassName1, false),
    
    std::make_unique<juce::AudioParameterBool>(juce::ParameterID {ProcessingConstants::Distortion::Identifiers::distortionBypassedID2, 5},
                                               ProcessingConstants::Distortion::Identifiers::distortionBypassName2, false),
    
    std::make_unique<juce::AudioParameterBool>(juce::ParameterID {ProcessingConstants::Distortion::Identifiers::distortionBypassedID3, 5},
                                               ProcessingConstants::Distortion::Identifiers::distortionBypassName3, false),
    
    std::make_unique<juce::AudioParameterBool>(juce::ParameterID {ProcessingConstants::Distortion::Identifiers::distortionBypassedID4, 5},
                                               ProcessingConstants::Distortion::Identifiers::distortionBypassName4, false),
    
    // Envelope Filter
    // ================================================================================================================================
    
        // Quality
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterQualityID1, 6},
                                                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterQualityName1,
                                                juce::NormalisableRange<float>(ProcessingConstants::EnvelopeFilter::Numeric::qualityMin,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::qualityMax,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::qualityIncrement,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::qualitySkew),
                                                ProcessingConstants::EnvelopeFilter::Numeric::defaultQuality),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterQualityID2, 6},
                                                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterQualityName2,
                                                juce::NormalisableRange<float>(ProcessingConstants::EnvelopeFilter::Numeric::qualityMin,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::qualityMax,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::qualityIncrement,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::qualitySkew),
                                                ProcessingConstants::EnvelopeFilter::Numeric::defaultQuality),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterQualityID3, 6},
                                                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterQualityName3,
                                                juce::NormalisableRange<float>(ProcessingConstants::EnvelopeFilter::Numeric::qualityMin,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::qualityMax,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::qualityIncrement,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::qualitySkew),
                                                ProcessingConstants::EnvelopeFilter::Numeric::defaultQuality),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterQualityID4, 6},
                                                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterQualityName4,
                                                juce::NormalisableRange<float>(ProcessingConstants::EnvelopeFilter::Numeric::qualityMin,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::qualityMax,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::qualityIncrement,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::qualitySkew),
                                                ProcessingConstants::EnvelopeFilter::Numeric::defaultQuality),
    
    
        // Sensitivity
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterSensitivityID1, 6},
                                                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterSensitivityName1,
                                                juce::NormalisableRange<float>(ProcessingConstants::EnvelopeFilter::Numeric::sensitivityMin,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::sensitivityMax,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::sensitivityIncrement,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::sensitivitySkew),
                                                ProcessingConstants::EnvelopeFilter::Numeric::defaultSensitivity),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterSensitivityID2, 6},
                                                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterSensitivityName2,
                                                juce::NormalisableRange<float>(ProcessingConstants::EnvelopeFilter::Numeric::sensitivityMin,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::sensitivityMax,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::sensitivityIncrement,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::sensitivitySkew),
                                                ProcessingConstants::EnvelopeFilter::Numeric::defaultSensitivity),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterSensitivityID3, 6},
                                                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterSensitivityName3,
                                                juce::NormalisableRange<float>(ProcessingConstants::EnvelopeFilter::Numeric::sensitivityMin,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::sensitivityMax,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::sensitivityIncrement,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::sensitivitySkew),
                                                ProcessingConstants::EnvelopeFilter::Numeric::defaultSensitivity),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterSensitivityID4, 6},
                                                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterSensitivityName4,
                                                juce::NormalisableRange<float>(ProcessingConstants::EnvelopeFilter::Numeric::sensitivityMin,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::sensitivityMax,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::sensitivityIncrement,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::sensitivitySkew),
                                                ProcessingConstants::EnvelopeFilter::Numeric::defaultSensitivity),
    
        // Cutoff Threshold
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterCutoffThresholdID1, 6},
                                                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterCutoffThresholdName1,
                                                juce::NormalisableRange<float>(ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdMin,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdMax,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdIncrement,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdSkew),
                                                ProcessingConstants::EnvelopeFilter::Numeric::defaultCutoffThreshold),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterCutoffThresholdID2, 6},
                                                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterCutoffThresholdName2,
                                                juce::NormalisableRange<float>(ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdMin,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdMax,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdIncrement,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdSkew),
                                                ProcessingConstants::EnvelopeFilter::Numeric::defaultCutoffThreshold),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterCutoffThresholdID3, 6},
                                                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterCutoffThresholdName3,
                                                juce::NormalisableRange<float>(ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdMin,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdMax,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdIncrement,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdSkew),
                                                ProcessingConstants::EnvelopeFilter::Numeric::defaultCutoffThreshold),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterCutoffThresholdID4, 6},
                                                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterCutoffThresholdName4,
                                                juce::NormalisableRange<float>(ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdMin,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdMax,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdIncrement,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdSkew),
                                                ProcessingConstants::EnvelopeFilter::Numeric::defaultCutoffThreshold),
    
        // Bypass
    
    std::make_unique<juce::AudioParameterBool>(juce::ParameterID {ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterBypassedID1, 6},
                                               ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterBypassName1, false),
    
    std::make_unique<juce::AudioParameterBool>(juce::ParameterID {ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterBypassedID2, 6},
                                               ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterBypassName2, false),
    
    std::make_unique<juce::AudioParameterBool>(juce::ParameterID {ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterBypassedID3, 6},
                                               ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterBypassName3, false),
    
    std::make_unique<juce::AudioParameterBool>(juce::ParameterID {ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterBypassedID4, 6},
                                               ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterBypassName4, false),
    
    
}
