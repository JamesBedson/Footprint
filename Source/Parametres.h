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
                                                                               ProcessingConstants::EditorControls::Numeric::outputGainIncrement),
                                                ProcessingConstants::EditorControls::Numeric::defaultOutputGain),
    
    std::make_unique<juce::AudioParameterBool>(juce::ParameterID {ProcessingConstants::EditorControls::Identifiers::monoStereoParam, 1},
                                               ProcessingConstants::EditorControls::Identifiers::monoStereoID,
                                               ProcessingConstants::EditorControls::Numeric::isStereo),
    
    // Pedal Slots
    
    std::make_unique<juce::AudioParameterChoice>(juce::ParameterID {ProcessingConstants::Pedals::Identifiers::slot1Param, 1},
                                                 ProcessingConstants::Pedals::Identifiers::slot1ID,
                                                 ProcessingConstants::Pedals::Choices::choiceArray,
                                                 0),
    
    std::make_unique<juce::AudioParameterChoice>(juce::ParameterID {ProcessingConstants::Pedals::Identifiers::slot2Param, 2},
                                                 ProcessingConstants::Pedals::Identifiers::slot2ID,
                                                 ProcessingConstants::Pedals::Choices::choiceArray,
                                                 0),
    
    std::make_unique<juce::AudioParameterChoice>(juce::ParameterID {ProcessingConstants::Pedals::Identifiers::slot3Param, 3},
                                                 ProcessingConstants::Pedals::Identifiers::slot3ID,
                                                 ProcessingConstants::Pedals::Choices::choiceArray,
                                                 0),
    
    std::make_unique<juce::AudioParameterChoice>(juce::ParameterID {ProcessingConstants::Pedals::Identifiers::slot4Param, 4},
                                                 ProcessingConstants::Pedals::Identifiers::slot4ID,
                                                 ProcessingConstants::Pedals::Choices::choiceArray,
                                                 0),
    
    // Compressor
    // ================================================================================================================================
    
        // Attack
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorAttack1, 1},
                                                ProcessingConstants::Compressor::Identifiers::compressorAttackID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Compressor::Numeric::attackMin,
                                                                               ProcessingConstants::Compressor::Numeric::attackMax,
                                                                               ProcessingConstants::Compressor::Numeric::attackIncrement,
                                                                               ProcessingConstants::Compressor::Numeric::attackSkew),
                                                ProcessingConstants::Compressor::Numeric::defaultAttack),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorAttack2, 2},
                                                ProcessingConstants::Compressor::Identifiers::compressorAttackID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Compressor::Numeric::attackMin,
                                                                               ProcessingConstants::Compressor::Numeric::attackMax,
                                                                               ProcessingConstants::Compressor::Numeric::attackIncrement,
                                                                               ProcessingConstants::Compressor::Numeric::attackSkew),
                                                ProcessingConstants::Compressor::Numeric::defaultAttack),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorAttack3, 3},
                                                ProcessingConstants::Compressor::Identifiers::compressorAttackID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Compressor::Numeric::attackMin,
                                                                               ProcessingConstants::Compressor::Numeric::attackMax,
                                                                               ProcessingConstants::Compressor::Numeric::attackIncrement,
                                                                               ProcessingConstants::Compressor::Numeric::attackSkew),
                                                ProcessingConstants::Compressor::Numeric::defaultAttack),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorAttack4, 4},
                                                ProcessingConstants::Compressor::Identifiers::compressorAttackID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Compressor::Numeric::attackMin,
                                                                               ProcessingConstants::Compressor::Numeric::attackMax,
                                                                               ProcessingConstants::Compressor::Numeric::attackIncrement,
                                                                               ProcessingConstants::Compressor::Numeric::attackSkew),
                                                ProcessingConstants::Compressor::Numeric::defaultAttack),
        // Release
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorRelease1, 1},
                                                ProcessingConstants::Compressor::Identifiers::compressotReleaseID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Compressor::Numeric::releaseMin,
                                                                               ProcessingConstants::Compressor::Numeric::releaseMax,
                                                                               ProcessingConstants::Compressor::Numeric::releaseIncrement,
                                                                               ProcessingConstants::Compressor::Numeric::releaseSkew),
                                                ProcessingConstants::Compressor::Numeric::defaultRelease),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorRelease2, 2},
                                                ProcessingConstants::Compressor::Identifiers::compressotReleaseID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Compressor::Numeric::releaseMin,
                                                                               ProcessingConstants::Compressor::Numeric::releaseMax,
                                                                               ProcessingConstants::Compressor::Numeric::releaseIncrement,
                                                                               ProcessingConstants::Compressor::Numeric::releaseSkew),
                                                ProcessingConstants::Compressor::Numeric::defaultRelease),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorRelease3, 3},
                                                ProcessingConstants::Compressor::Identifiers::compressotReleaseID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Compressor::Numeric::releaseMin,
                                                                               ProcessingConstants::Compressor::Numeric::releaseMax,
                                                                               ProcessingConstants::Compressor::Numeric::releaseIncrement,
                                                                               ProcessingConstants::Compressor::Numeric::releaseSkew),
                                                ProcessingConstants::Compressor::Numeric::defaultRelease),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorRelease4, 4},
                                                ProcessingConstants::Compressor::Identifiers::compressotReleaseID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Compressor::Numeric::releaseMin,
                                                                               ProcessingConstants::Compressor::Numeric::releaseMax,
                                                                               ProcessingConstants::Compressor::Numeric::releaseIncrement,
                                                                               ProcessingConstants::Compressor::Numeric::releaseSkew),
                                                ProcessingConstants::Compressor::Numeric::defaultRelease),
    
        // Threshold
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorThreshold1, 1},
                                                ProcessingConstants::Compressor::Identifiers::compressorThresholdID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Compressor::Numeric::thresholdMin,
                                                                               ProcessingConstants::Compressor::Numeric::thresholdMax,
                                                                               ProcessingConstants::Compressor::Numeric::thresholdIncrement,
                                                                               ProcessingConstants::Compressor::Numeric::thresholdSkew),
                                                ProcessingConstants::Compressor::Numeric::defaultThreshold),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorThreshold2, 2},
                                                ProcessingConstants::Compressor::Identifiers::compressorThresholdID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Compressor::Numeric::thresholdMin,
                                                                               ProcessingConstants::Compressor::Numeric::thresholdMax,
                                                                               ProcessingConstants::Compressor::Numeric::thresholdIncrement,
                                                                               ProcessingConstants::Compressor::Numeric::thresholdSkew),
                                                ProcessingConstants::Compressor::Numeric::defaultThreshold),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorThreshold3, 3},
                                                ProcessingConstants::Compressor::Identifiers::compressorThresholdID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Compressor::Numeric::thresholdMin,
                                                                               ProcessingConstants::Compressor::Numeric::thresholdMax,
                                                                               ProcessingConstants::Compressor::Numeric::thresholdIncrement,
                                                                               ProcessingConstants::Compressor::Numeric::thresholdSkew),
                                                ProcessingConstants::Compressor::Numeric::defaultThreshold),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorThreshold4, 4},
                                                ProcessingConstants::Compressor::Identifiers::compressorThresholdID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Compressor::Numeric::thresholdMin,
                                                                               ProcessingConstants::Compressor::Numeric::thresholdMax,
                                                                               ProcessingConstants::Compressor::Numeric::thresholdIncrement,
                                                                               ProcessingConstants::Compressor::Numeric::thresholdSkew),
                                                ProcessingConstants::Compressor::Numeric::defaultThreshold),
    
        // Ratio
    
    std::make_unique<juce::AudioParameterInt>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorRatio1, 1},
                                              ProcessingConstants::Compressor::Identifiers::compressorRatioID,
                                              ProcessingConstants::Compressor::Numeric::ratioMin,
                                              ProcessingConstants::Compressor::Numeric::ratioMax,
                                              ProcessingConstants::Compressor::Numeric::defaultRatio),
    
    std::make_unique<juce::AudioParameterInt>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorRatio2, 2},
                                              ProcessingConstants::Compressor::Identifiers::compressorRatioID,
                                              ProcessingConstants::Compressor::Numeric::ratioMin,
                                              ProcessingConstants::Compressor::Numeric::ratioMax,
                                              ProcessingConstants::Compressor::Numeric::defaultRatio),
    
    std::make_unique<juce::AudioParameterInt>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorRatio3, 3},
                                              ProcessingConstants::Compressor::Identifiers::compressorRatioID,
                                              ProcessingConstants::Compressor::Numeric::ratioMin,
                                              ProcessingConstants::Compressor::Numeric::ratioMax,
                                              ProcessingConstants::Compressor::Numeric::defaultRatio),
    
    std::make_unique<juce::AudioParameterInt>(juce::ParameterID {ProcessingConstants::Compressor::Identifiers::compressorRatio4, 4},
                                              ProcessingConstants::Compressor::Identifiers::compressorRatioID,
                                              ProcessingConstants::Compressor::Numeric::ratioMin,
                                              ProcessingConstants::Compressor::Numeric::ratioMax,
                                              ProcessingConstants::Compressor::Numeric::defaultRatio),
    
    // Reverb
    // ================================================================================================================================
    
        // Wet/Dry
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Reverb::Identifiers::reverbWetMix1, 1},
                                                ProcessingConstants::Reverb::Identifiers::reverbWetMixID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Reverb::Numeric::wetMin,
                                                                               ProcessingConstants::Reverb::Numeric::wetMax,
                                                                               ProcessingConstants::Reverb::Numeric::wetIncrement,
                                                                               ProcessingConstants::Reverb::Numeric::wetSkew),
                                                ProcessingConstants::Reverb::Numeric::defaultWetMix),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Reverb::Identifiers::reverbWetMix2, 2},
                                                ProcessingConstants::Reverb::Identifiers::reverbWetMixID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Reverb::Numeric::wetMin,
                                                                               ProcessingConstants::Reverb::Numeric::wetMax,
                                                                               ProcessingConstants::Reverb::Numeric::wetIncrement,
                                                                               ProcessingConstants::Reverb::Numeric::wetSkew),
                                                ProcessingConstants::Reverb::Numeric::defaultWetMix),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Reverb::Identifiers::reverbWetMix3, 3},
                                                ProcessingConstants::Reverb::Identifiers::reverbWetMixID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Reverb::Numeric::wetMin,
                                                                               ProcessingConstants::Reverb::Numeric::wetMax,
                                                                               ProcessingConstants::Reverb::Numeric::wetIncrement,
                                                                               ProcessingConstants::Reverb::Numeric::wetSkew),
                                                ProcessingConstants::Reverb::Numeric::defaultWetMix),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Reverb::Identifiers::reverbWetMix4, 4},
                                                ProcessingConstants::Reverb::Identifiers::reverbWetMixID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Reverb::Numeric::wetMin,
                                                                               ProcessingConstants::Reverb::Numeric::wetMax,
                                                                               ProcessingConstants::Reverb::Numeric::wetIncrement,
                                                                               ProcessingConstants::Reverb::Numeric::wetSkew),
                                                ProcessingConstants::Reverb::Numeric::defaultWetMix),
    
        // Cutoff Lowpass
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Reverb::Identifiers::reverbCutoffLowpass1, 1},
                                                ProcessingConstants::Reverb::Identifiers::reverbLowpassID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Reverb::Numeric::cutoffLowpassMin,
                                                                               ProcessingConstants::Reverb::Numeric::cutoffLowpassMax,
                                                                               ProcessingConstants::Reverb::Numeric::cutoffLowpassIncrement,
                                                                               ProcessingConstants::Reverb::Numeric::cutoffLowpassSkew),
                                                ProcessingConstants::Reverb::Numeric::defaultCuttoffLowpass),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Reverb::Identifiers::reverbCutoffLowpass2, 2},
                                                ProcessingConstants::Reverb::Identifiers::reverbLowpassID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Reverb::Numeric::cutoffLowpassMin,
                                                                               ProcessingConstants::Reverb::Numeric::cutoffLowpassMax,
                                                                               ProcessingConstants::Reverb::Numeric::cutoffLowpassIncrement,
                                                                               ProcessingConstants::Reverb::Numeric::cutoffLowpassSkew),
                                                ProcessingConstants::Reverb::Numeric::defaultCuttoffLowpass),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Reverb::Identifiers::reverbCutoffLowpass3, 3},
                                                ProcessingConstants::Reverb::Identifiers::reverbLowpassID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Reverb::Numeric::cutoffLowpassMin,
                                                                               ProcessingConstants::Reverb::Numeric::cutoffLowpassMax,
                                                                               ProcessingConstants::Reverb::Numeric::cutoffLowpassIncrement,
                                                                               ProcessingConstants::Reverb::Numeric::cutoffLowpassSkew),
                                                ProcessingConstants::Reverb::Numeric::defaultCuttoffLowpass),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Reverb::Identifiers::reverbCutoffLowpass4, 4},
                                                ProcessingConstants::Reverb::Identifiers::reverbLowpassID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Reverb::Numeric::cutoffLowpassMin,
                                                                               ProcessingConstants::Reverb::Numeric::cutoffLowpassMax,
                                                                               ProcessingConstants::Reverb::Numeric::cutoffLowpassIncrement,
                                                                               ProcessingConstants::Reverb::Numeric::cutoffLowpassSkew),
                                                ProcessingConstants::Reverb::Numeric::defaultCuttoffLowpass),
    
        // Cutoff Highpass
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Reverb::Identifiers::reverbCutoffHighpass1, 1},
                                                ProcessingConstants::Reverb::Identifiers::reverbHighpassID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Reverb::Numeric::cutoffHighpassMin,
                                                                               ProcessingConstants::Reverb::Numeric::cutoffHighpassMax,
                                                                               ProcessingConstants::Reverb::Numeric::cutoffHighpassIncrement,
                                                                               ProcessingConstants::Reverb::Numeric::cutoffHighpassSkew),
                                                ProcessingConstants::Reverb::Numeric::defaultCutoffHighpass),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Reverb::Identifiers::reverbCutoffHighpass2, 2},
                                                ProcessingConstants::Reverb::Identifiers::reverbHighpassID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Reverb::Numeric::cutoffHighpassMin,
                                                                               ProcessingConstants::Reverb::Numeric::cutoffHighpassMax,
                                                                               ProcessingConstants::Reverb::Numeric::cutoffHighpassIncrement,
                                                                               ProcessingConstants::Reverb::Numeric::cutoffHighpassSkew),
                                                ProcessingConstants::Reverb::Numeric::defaultCutoffHighpass),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Reverb::Identifiers::reverbCutoffHighpass3, 3},
                                                ProcessingConstants::Reverb::Identifiers::reverbHighpassID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Reverb::Numeric::cutoffHighpassMin,
                                                                               ProcessingConstants::Reverb::Numeric::cutoffHighpassMax,
                                                                               ProcessingConstants::Reverb::Numeric::cutoffHighpassIncrement,
                                                                               ProcessingConstants::Reverb::Numeric::cutoffHighpassSkew),
                                                ProcessingConstants::Reverb::Numeric::defaultCutoffHighpass),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Reverb::Identifiers::reverbCutoffHighpass4, 4},
                                                ProcessingConstants::Reverb::Identifiers::reverbHighpassID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Reverb::Numeric::cutoffHighpassMin,
                                                                               ProcessingConstants::Reverb::Numeric::cutoffHighpassMax,
                                                                               ProcessingConstants::Reverb::Numeric::cutoffHighpassIncrement,
                                                                               ProcessingConstants::Reverb::Numeric::cutoffHighpassSkew),
                                                ProcessingConstants::Reverb::Numeric::defaultCutoffHighpass),
    
    
    // Distortion
    // ================================================================================================================================
    
        // Gain
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Distortion::Identifiers::distortionGain1, 1},
                                                ProcessingConstants::Distortion::Identifiers::distortionGainID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Distortion::Numeric::minGainDecibels,
                                                                               ProcessingConstants::Distortion::Numeric::maxGainDecibels,
                                                                               ProcessingConstants::Distortion::Numeric::gainIncrement,
                                                                               ProcessingConstants::Distortion::Numeric::gainskew),
                                                ProcessingConstants::Distortion::Numeric::defaultGainDecibels),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Distortion::Identifiers::distortionGain2, 2},
                                                ProcessingConstants::Distortion::Identifiers::distortionGainID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Distortion::Numeric::minGainDecibels,
                                                                               ProcessingConstants::Distortion::Numeric::maxGainDecibels,
                                                                               ProcessingConstants::Distortion::Numeric::gainIncrement,
                                                                               ProcessingConstants::Distortion::Numeric::gainskew),
                                                ProcessingConstants::Distortion::Numeric::defaultGainDecibels),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Distortion::Identifiers::distortionGain3, 3},
                                                ProcessingConstants::Distortion::Identifiers::distortionGainID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Distortion::Numeric::minGainDecibels,
                                                                               ProcessingConstants::Distortion::Numeric::maxGainDecibels,
                                                                               ProcessingConstants::Distortion::Numeric::gainIncrement,
                                                                               ProcessingConstants::Distortion::Numeric::gainskew),
                                                ProcessingConstants::Distortion::Numeric::defaultGainDecibels),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Distortion::Identifiers::distortionGain4, 4},
                                                ProcessingConstants::Distortion::Identifiers::distortionGainID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Distortion::Numeric::minGainDecibels,
                                                                               ProcessingConstants::Distortion::Numeric::maxGainDecibels,
                                                                               ProcessingConstants::Distortion::Numeric::gainIncrement,
                                                                               ProcessingConstants::Distortion::Numeric::gainskew),
                                                ProcessingConstants::Distortion::Numeric::defaultGainDecibels),
    
    
        // Level
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Distortion::Identifiers::distortionLevel1, 1},
                                                ProcessingConstants::Distortion::Identifiers::distortionLevelID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Distortion::Numeric::minLevel,
                                                                               ProcessingConstants::Distortion::Numeric::maxLevel,
                                                                               ProcessingConstants::Distortion::Numeric::levelIncrement,
                                                                               ProcessingConstants::Distortion::Numeric::levelSkew),
                                                ProcessingConstants::Distortion::Numeric::defaultLevel),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Distortion::Identifiers::distortionLevel2, 2},
                                                ProcessingConstants::Distortion::Identifiers::distortionLevelID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Distortion::Numeric::minLevel,
                                                                               ProcessingConstants::Distortion::Numeric::maxLevel,
                                                                               ProcessingConstants::Distortion::Numeric::levelIncrement,
                                                                               ProcessingConstants::Distortion::Numeric::levelSkew),
                                                ProcessingConstants::Distortion::Numeric::defaultLevel),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Distortion::Identifiers::distortionLevel3, 3},
                                                ProcessingConstants::Distortion::Identifiers::distortionLevelID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Distortion::Numeric::minLevel,
                                                                               ProcessingConstants::Distortion::Numeric::maxLevel,
                                                                               ProcessingConstants::Distortion::Numeric::levelIncrement,
                                                                               ProcessingConstants::Distortion::Numeric::levelSkew),
                                                ProcessingConstants::Distortion::Numeric::defaultLevel),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Distortion::Identifiers::distortionLevel4, 4},
                                                ProcessingConstants::Distortion::Identifiers::distortionLevelID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Distortion::Numeric::minLevel,
                                                                               ProcessingConstants::Distortion::Numeric::maxLevel,
                                                                               ProcessingConstants::Distortion::Numeric::levelIncrement,
                                                                               ProcessingConstants::Distortion::Numeric::levelSkew),
                                                ProcessingConstants::Distortion::Numeric::defaultLevel),
    
    
        // Tone
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Distortion::Identifiers::distortionTone1, 1},
                                                ProcessingConstants::Distortion::Identifiers::distortionToneID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Distortion::Numeric::minTone,
                                                                               ProcessingConstants::Distortion::Numeric::maxTone,
                                                                               ProcessingConstants::Distortion::Numeric::toneIncrement,
                                                                               ProcessingConstants::Distortion::Numeric::toneSkew),
                                                ProcessingConstants::Distortion::Numeric::defaultTone),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Distortion::Identifiers::distortionTone2, 2},
                                                ProcessingConstants::Distortion::Identifiers::distortionToneID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Distortion::Numeric::minTone,
                                                                               ProcessingConstants::Distortion::Numeric::maxTone,
                                                                               ProcessingConstants::Distortion::Numeric::toneIncrement,
                                                                               ProcessingConstants::Distortion::Numeric::toneSkew),
                                                ProcessingConstants::Distortion::Numeric::defaultTone),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Distortion::Identifiers::distortionTone3, 3},
                                                ProcessingConstants::Distortion::Identifiers::distortionToneID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Distortion::Numeric::minTone,
                                                                               ProcessingConstants::Distortion::Numeric::maxTone,
                                                                               ProcessingConstants::Distortion::Numeric::toneIncrement,
                                                                               ProcessingConstants::Distortion::Numeric::toneSkew),
                                                ProcessingConstants::Distortion::Numeric::defaultTone),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::Distortion::Identifiers::distortionTone4, 4},
                                                ProcessingConstants::Distortion::Identifiers::distortionToneID,
                                                juce::NormalisableRange<float>(ProcessingConstants::Distortion::Numeric::minTone,
                                                                               ProcessingConstants::Distortion::Numeric::maxTone,
                                                                               ProcessingConstants::Distortion::Numeric::toneIncrement,
                                                                               ProcessingConstants::Distortion::Numeric::toneSkew),
                                                ProcessingConstants::Distortion::Numeric::defaultTone),
    
    // Envelope Filter
    // ================================================================================================================================
    
        // Quality
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterQuality1, 1},
                                                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterQualityID,
                                                juce::NormalisableRange<float>(ProcessingConstants::EnvelopeFilter::Numeric::qualityMin,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::qualityMax,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::qualityIncrement,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::qualitySkew),
                                                ProcessingConstants::EnvelopeFilter::Numeric::defaultQuality),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterQuality2, 2},
                                                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterQualityID,
                                                juce::NormalisableRange<float>(ProcessingConstants::EnvelopeFilter::Numeric::qualityMin,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::qualityMax,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::qualityIncrement,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::qualitySkew),
                                                ProcessingConstants::EnvelopeFilter::Numeric::defaultQuality),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterQuality3, 3},
                                                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterQualityID,
                                                juce::NormalisableRange<float>(ProcessingConstants::EnvelopeFilter::Numeric::qualityMin,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::qualityMax,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::qualityIncrement,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::qualitySkew),
                                                ProcessingConstants::EnvelopeFilter::Numeric::defaultQuality),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterQuality4, 4},
                                                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterQualityID,
                                                juce::NormalisableRange<float>(ProcessingConstants::EnvelopeFilter::Numeric::qualityMin,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::qualityMax,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::qualityIncrement,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::qualitySkew),
                                                ProcessingConstants::EnvelopeFilter::Numeric::defaultQuality),
    
    
        // Sensitivity
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterSensitivity1, 1},
                                                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterSensitivityID,
                                                juce::NormalisableRange<float>(ProcessingConstants::EnvelopeFilter::Numeric::sensitivityMin,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::sensitivityMax,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::sensitivityIncrement,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::sensitivitySkew),
                                                ProcessingConstants::EnvelopeFilter::Numeric::defaultSensitivity),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterSensitivity2, 2},
                                                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterSensitivityID,
                                                juce::NormalisableRange<float>(ProcessingConstants::EnvelopeFilter::Numeric::sensitivityMin,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::sensitivityMax,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::sensitivityIncrement,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::sensitivitySkew),
                                                ProcessingConstants::EnvelopeFilter::Numeric::defaultSensitivity),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterSensitivity3, 3},
                                                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterSensitivityID,
                                                juce::NormalisableRange<float>(ProcessingConstants::EnvelopeFilter::Numeric::sensitivityMin,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::sensitivityMax,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::sensitivityIncrement,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::sensitivitySkew),
                                                ProcessingConstants::EnvelopeFilter::Numeric::defaultSensitivity),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterSensitivity4, 4},
                                                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterSensitivityID,
                                                juce::NormalisableRange<float>(ProcessingConstants::EnvelopeFilter::Numeric::sensitivityMin,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::sensitivityMax,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::sensitivityIncrement,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::sensitivitySkew),
                                                ProcessingConstants::EnvelopeFilter::Numeric::defaultSensitivity),
    
        // Cutoff Threshold
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterCutoffThreshold1, 1},
                                                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterCutoffThresholdID,
                                                juce::NormalisableRange<float>(ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdMin,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdMax,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdIncrement,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdSkew),
                                                ProcessingConstants::EnvelopeFilter::Numeric::defaultCutoffThreshold),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterCutoffThreshold2, 2},
                                                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterCutoffThresholdID,
                                                juce::NormalisableRange<float>(ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdMin,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdMax,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdIncrement,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdSkew),
                                                ProcessingConstants::EnvelopeFilter::Numeric::defaultCutoffThreshold),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterCutoffThreshold3, 3},
                                                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterCutoffThresholdID,
                                                juce::NormalisableRange<float>(ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdMin,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdMax,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdIncrement,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdSkew),
                                                ProcessingConstants::EnvelopeFilter::Numeric::defaultCutoffThreshold),
    
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterCutoffThreshold4, 4},
                                                ProcessingConstants::EnvelopeFilter::Identifiers::envelopeFilterCutoffThresholdID,
                                                juce::NormalisableRange<float>(ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdMin,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdMax,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdIncrement,
                                                                               ProcessingConstants::EnvelopeFilter::Numeric::cutoffThresholdSkew),
                                                ProcessingConstants::EnvelopeFilter::Numeric::defaultCutoffThreshold),
    
    
}
