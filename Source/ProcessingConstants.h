/*
  ==============================================================================

    ProcessingConstants.h
    Created: 23 May 2023 5:39:09pm
    Author:  James Bedson

  ==============================================================================
*/

#pragma once
#include <string>

namespace ProcessingConstants {

namespace EditorControls {

namespace Numeric {

const float inputGainMin            = 0.f;
const float inputGainMax            = 2.f;
const float inputGainIncrement      = 0.01f;
const float inputGainSkew           = 0.3f;
const float defaultInputGain        = 1.f;

const float outputGainMin           = 0.f;
const float outputGainMax           = 2.f;
const float outputGainIncrement     = 0.01f;
const float outputGainSkew          = 0.3f;
const float defaultOutputGain       = 1.f;

const bool  isStereo                = true;

}

namespace Identifiers {
    
const std::string inputGainID       = "Input Gain";
const std::string inputGainParam    = "input_gain";

const std::string outputGainID      = "Output Gain";
const std::string outputGainParam   = "output_gain";

const std::string monoStereoID      = "Mono/Stereo";
const std::string monoStereoParam   = "mono_stereo";


    }

}

namespace Pedals {


namespace Choices {

const std::string noPedal           = "No Pedal";
const std::string compressor        = "Compressor";
const std::string envelopeFilter    = "Envelope Filter";
const std::string reverb            = "Reverb";
const std::string distortion        = "Distortion";

const juce::StringArray choiceArray
{
    noPedal,
    compressor,
    distortion,
    envelopeFilter,
    reverb
};


}

    namespace Identifiers  {

    const std::string slot1Param    = "slot_1";
    const std::string slot2Param    = "slot_2";
    const std::string slot3Param    = "slot_3";
    const std::string slot4Param    = "slot_4";

    const std::string slot1ID       = "Pedal Slot 1";
    const std::string slot2ID       = "Pedal Slot 2";
    const std::string slot3ID       = "Pedal Slot 3";
    const std::string slot4ID       = "Pedal Slot 4";
    }

}

    namespace Compressor {

        namespace Numeric {
        
        const float attackMin           = 0.01f;
        const float attackMax           = 0.5f;
        const float attackIncrement     = 0.01f;
        const float attackSkew          = 1.f;
        
        const float releaseMin          = 0.01f;
        const float releaseMax          = 0.5f;
        const float releaseIncrement    = 0.01f;
        const float releaseSkew         = 1.f;
        
        const float thresholdMin        = -64.f;
        const float thresholdMax        = 10.f; 
        const float thresholdIncrement  = 0.5f;
        const float thresholdSkew       = 1.f;
        
        const int   ratioMin            = 1;
        const int   ratioMax            = 15;

        const float defaultAttack       = 0.1f;
        const float defaultRelease      = 0.1f;
        const float defaultThreshold    = -40.f;
        const int   defaultRatio        = 2;

        } // Numeric

        namespace Identifiers {
        
        const std::string compressorAttackName1     = "Compressor: Attack (Slot 1)";
        const std::string compressorAttackName2     = "Compressor: Attack (Slot 2)";
        const std::string compressorAttackName3     = "Compressor: Attack (Slot 3)";
        const std::string compressorAttackName4     = "Compressor: Attack (Slot 4)";
        
        const std::string compressotReleaseName1    = "Compressor: Release (Slot 1)";
        const std::string compressotReleaseName2    = "Compressor: Release (Slot 2)";
        const std::string compressotReleaseName3    = "Compressor: Release (Slot 3)";
        const std::string compressotReleaseName4    = "Compressor: Release (Slot 4)";
        
        const std::string compressorThresholdName1  = "Compressor: Threshold (Slot 1)";
        const std::string compressorThresholdName2  = "Compressor: Threshold (Slot 2)";
        const std::string compressorThresholdName3  = "Compressor: Threshold (Slot 3)";
        const std::string compressorThresholdName4  = "Compressor: Threshold (Slot 4)";
        
        const std::string compressorRatioName1      = "Compressor: Ratio (Slot 1)";
        const std::string compressorRatioName2      = "Compressor: Ratio (Slot 2)";
        const std::string compressorRatioName3      = "Compressor: Ratio (Slot 3)";
        const std::string compressorRatioName4      = "Compressor: Ratio (Slot 4)";
        
        const std::string compressorBypassName1     = "Compressor: Bypass (Slot 1)";
        const std::string compressorBypassName2     = "Compressor: Bypass (Slot 2)";
        const std::string compressorBypassName3     = "Compressor: Bypass (Slot 3)";
        const std::string compressorBypassName4     = "Compressor: Bypass (Slot 4)";

        const std::string compressorAttackID1       = "attack_1";
        const std::string compressorAttackID2       = "attack_2";
        const std::string compressorAttackID3       = "attack_3";
        const std::string compressorAttackID4       = "attack_4";

        const std::string compressorReleaseID1      = "release_1";
        const std::string compressorReleaseID2      = "release_2";
        const std::string compressorReleaseID3      = "release_3";
        const std::string compressorReleaseID4      = "release_4";

        const std::string compressorThresholdID1    = "threshold_1";
        const std::string compressorThresholdID2    = "threshold_2";
        const std::string compressorThresholdID3    = "threshold_3";
        const std::string compressorThresholdID4    = "threshold_4";

        const std::string compressorRatioID1        = "ratio_1";
        const std::string compressorRatioID2        = "ratio_2";
        const std::string compressorRatioID3        = "ratio_3";
        const std::string compressorRatioID4        = "ratio_4";
        
        const std::string compressorBypassedID1       = "compressor_bypassed_1";
        const std::string compressorBypassedID2       = "compressor_bypassed_2";
        const std::string compressorBypassedID3       = "compressor_bypassed_3";
        const std::string compressorBypassedID4       = "compressor_bypassed_4";

        } // IDs
    
    } // Compressor


    namespace Reverb {
        
        namespace IRChoices {
        
        const juce::StringArray irChoiceArray {
            "bathroom",
            "aranyoShort",
            "aranyoLarge",
            "corridor"
        };
        
        }
    
        namespace Numeric {

        const float wetMin                  = 0.f;
        const float wetMax                  = 1.f;
        const float wetIncrement            = 0.01f;
        const float wetSkew                 = 1.f;
            
        const float defaultWetMix           = 50.f;
        const int   defaultIRChoice         = 3;
        }

        namespace Identifiers {
        
        const std::string reverbWetMixName1       = "Reverb: Mix (Slot 1)";
        const std::string reverbWetMixName2       = "Reverb: Mix (Slot 2)";
        const std::string reverbWetMixName3       = "Reverb: Mix (Slot 3)";
        const std::string reverbWetMixName4       = "Reverb: Mix (Slot 4)";
        
        const std::string reverbBypassName1       = "Reverb: Bypass (Slot 1)";
        const std::string reverbBypassName2       = "Reverb: Bypass (Slot 2)";
        const std::string reverbBypassName3       = "Reverb: Bypass (Slot 3)";
        const std::string reverbBypassName4       = "Reverb: Bypass (Slot 4)";
        
        const std::string reverbIRChoiceName1     = "Reverb: Impulse Response (Slot 1)";
        const std::string reverbIRChoiceName2     = "Reverb: Impulse Response (Slot 2)";
        const std::string reverbIRChoiceName3     = "Reverb: Impulse Response (Slot 3)";
        const std::string reverbIRChoiceName4     = "Reverb: Impulse Response (Slot 4)";
        
        const std::string reverbWetMixID1         = "wet_mix_1";
        const std::string reverbWetMixID2         = "wet_mix_2";
        const std::string reverbWetMixID3         = "wet_mix_3";
        const std::string reverbWetMixID4         = "wet_mix_4";
        
        const std::string reverbBypassedID1       = "reverb_bypassed_1";
        const std::string reverbBypassedID2       = "reverb_bypassed_2";
        const std::string reverbBypassedID3       = "reverb_bypassed_3";
        const std::string reverbBypassedID4       = "reverb_bypassed_4";
        
        const std::string reverbIRChoiceID1       = "reverb_IR_choice1";
        const std::string reverbIRChoiceID2       = "reverb_IR_choice2";
        const std::string reverbIRChoiceID3       = "reverb_IR_choice3";
        const std::string reverbIRChoiceID4       = "reverb_IR_choice4";
        
        }

    }

    namespace Distortion {

        namespace Numeric {

        const float minGainDecibels             = 1.f;
        const float maxGainDecibels             = 30.f;
        const float gainIncrement               = 0.5f;
        const float gainskew                    = 1.f;
        
        const float minLevel                    = 0.f;
        const float maxLevel                    = 1.f;
        const float levelIncrement              = 0.01f;
        const float levelSkew                   = 1.f;

        const float minTone                     = 0.05f;
        const float maxTone                     = 1.f;
        const float toneIncrement               = 0.01f;
        const float toneSkew                    = 1.f;
        
        const float defaultGainDecibels         = 0.f;
        const float defaultLevel                = 1.f;
        const float defaultTone                 = 0.6f;

        }

        namespace Identifiers {
        
        const std::string distortionGainName1   = "Distortion: Gain (Slot 1)";
        const std::string distortionGainName2   = "Distortion: Gain (Slot 2)";
        const std::string distortionGainName3   = "Distortion: Gain (Slot 3)";
        const std::string distortionGainName4   = "Distortion: Gain (Slot 4)";
        
        const std::string distortionLevelName1  = "Distortion: Level (Slot 1)";
        const std::string distortionLevelName2  = "Distortion: Level (Slot 2)";
        const std::string distortionLevelName3  = "Distortion: Level (Slot 3)";
        const std::string distortionLevelName4  = "Distortion: Level (Slot 4)";
        
        const std::string distortionToneName1   = "Distortion: Tone (Slot 1)";
        const std::string distortionToneName2   = "Distortion: Tone (Slot 2)";
        const std::string distortionToneName3   = "Distortion: Tone (Slot 3)";
        const std::string distortionToneName4   = "Distortion: Tone (Slot 4)";
        
        const std::string distortionBypassName1 = "Distortion: Bypass (Slot 1)";
        const std::string distortionBypassName2 = "Distortion: Bypass (Slot 2)";
        const std::string distortionBypassName3 = "Distortion: Bypass (Slot 3)";
        const std::string distortionBypassName4 = "Distortion: Bypass (Slot 4)";

        const std::string distortionGainID1     = "gain_1";
        const std::string distortionGainID2     = "gain_2";
        const std::string distortionGainID3     = "gain_3";
        const std::string distortionGainID4     = "gain_4";

        const std::string distortionLevelID1    = "level_1";
        const std::string distortionLevelID2    = "level_2";
        const std::string distortionLevelID3    = "level_3";
        const std::string distortionLevelID4    = "level_4";

        const std::string distortionToneID1     = "tone_1";
        const std::string distortionToneID2     = "tone_2";
        const std::string distortionToneID3     = "tone_3";
        const std::string distortionToneID4     = "tone_4";
        
        const std::string distortionBypassedID1 = "distortion_bypassed_1";
        const std::string distortionBypassedID2 = "distortion_bypassed_2";
        const std::string distortionBypassedID3 = "distortion_bypassed_3";
        const std::string distortionBypassedID4 = "distortion_bypassed_4";

        }

    }

    namespace EnvelopeFilter {

        namespace Numeric {

        const float qualityMin                  = 0.1f;
        const float qualityMax                  = 5.f;
        const float qualityIncrement            = 0.1f;
        const float qualitySkew                 = 1.f;
        
        const float sensitivityMin              = 0.1f;
        const float sensitivityMax              = 1.f;
        const float sensitivityIncrement        = 0.01f;
        const float sensitivitySkew             = 1.f;
        
        const float cutoffThresholdMin          = 100.f;
        const float cutoffThresholdMax          = 1000.f;
        const float cutoffThresholdIncrement    = 1.f;
        const float cutoffThresholdSkew         = 0.3f;
        
        const float defaultQuality              = 1.f;
        const float defaultSensitivity          = 1.f;
        const float defaultCutoffThreshold      = 300.f;

        }

        namespace Identifiers {
        
        const std::string envelopeFilterQualityName1        = "Envelope Filter: Quality (Slot 1)";
        const std::string envelopeFilterQualityName2        = "Envelope Filter: Quality (Slot 2)";
        const std::string envelopeFilterQualityName3        = "Envelope Filter: Quality (Slot 3)";
        const std::string envelopeFilterQualityName4        = "Envelope Filter: Quality (Slot 4)";
        
        const std::string envelopeFilterSensitivityName1    = "Envelope Filter: Sensitivity (Slot 1)";
        const std::string envelopeFilterSensitivityName2    = "Envelope Filter: Sensitivity (Slot 2)";
        const std::string envelopeFilterSensitivityName3    = "Envelope Filter: Sensitivity (Slot 3)";
        const std::string envelopeFilterSensitivityName4    = "Envelope Filter: Sensitivity (Slot 4)";
        
        const std::string envelopeFilterCutoffThresholdName1= "Envelope Filter: Cutoff Threshold (Slot 1)";
        const std::string envelopeFilterCutoffThresholdName2= "Envelope Filter: Cutoff Threshold (Slot 2)";
        const std::string envelopeFilterCutoffThresholdName3= "Envelope Filter: Cutoff Threshold (Slot 3)";
        const std::string envelopeFilterCutoffThresholdName4= "Envelope Filter: Cutoff Threshold (Slot 4)";
        
        const std::string envelopeFilterBypassName1         = "Envelope Filter: Bypass (Slot 1)";
        const std::string envelopeFilterBypassName2         = "Envelope Filter: Bypass (Slot 2)";
        const std::string envelopeFilterBypassName3         = "Envelope Filter: Bypass (Slot 3)";
        const std::string envelopeFilterBypassName4         = "Envelope Filter: Bypass (Slot 4)";

        const std::string envelopeFilterQualityID1            = "quality_1";
        const std::string envelopeFilterQualityID2            = "quality_2";
        const std::string envelopeFilterQualityID3            = "quality_3";
        const std::string envelopeFilterQualityID4            = "quality_4";

        const std::string envelopeFilterSensitivityID1        = "sensitivity_1";
        const std::string envelopeFilterSensitivityID2        = "sensitivity_2";
        const std::string envelopeFilterSensitivityID3        = "sensitivity_3";
        const std::string envelopeFilterSensitivityID4        = "sensitivity_4";
        
        const std::string envelopeFilterCutoffThresholdID1    = "cutoff_threshold_1";
        const std::string envelopeFilterCutoffThresholdID2    = "cutoff_threshold_2";
        const std::string envelopeFilterCutoffThresholdID3    = "cutoff_threshold_3";
        const std::string envelopeFilterCutoffThresholdID4    = "cutoff_threshold_4";
        
        const std::string envelopeFilterBypassedID1           = "envelope_filter_bypassed_1";
        const std::string envelopeFilterBypassedID2           = "envelope_filter_bypassed_2";
        const std::string envelopeFilterBypassedID3           = "envelope_filter_bypassed_3";
        const std::string envelopeFilterBypassedID4           = "envelope_filter_bypassed_4";

        }

    }

}
