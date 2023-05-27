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
        
        const std::string compressorAttackID    = "Compressor_Attack";
        const std::string compressotReleaseID   = "Compressor_Release";
        const std::string compressorThresholdID = "Compressor_Threshold";
        const std::string compressorRatioID     = "Compressor_Ratio";

        const std::string compressorAttack1     = "attack_1";
        const std::string compressorAttack2     = "attack_2";
        const std::string compressorAttack3     = "attack_3";
        const std::string compressorAttack4     = "attack_4";

        const std::string compressorRelease1    = "release_1";
        const std::string compressorRelease2    = "release_2";
        const std::string compressorRelease3    = "release_3";
        const std::string compressorRelease4    = "release_4";

        const std::string compressorThreshold1  = "threshold_1";
        const std::string compressorThreshold2  = "threshold_2";
        const std::string compressorThreshold3  = "threshold_3";
        const std::string compressorThreshold4  = "threshold_4";

        const std::string compressorRatio1      = "ratio_1";
        const std::string compressorRatio2      = "ratio_2";
        const std::string compressorRatio3      = "ratio_3";
        const std::string compressorRatio4      = "ratio_4";

        } // IDs
    
    } // Compressor


    namespace Reverb {

        namespace Numeric {

        const float wetMin                  = 0.f;
        const float wetMax                  = 100.f;
        const float wetIncrement            = 0.1f;
        const float wetSkew                 = 1.f;
        
        const float cutoffLowpassMin        = 150.f;
        const float cutoffLowpassMax        = 999.f;
        const float cutoffLowpassIncrement  = 1.f;
        const float cutoffLowpassSkew       = 0.3f;
        
        const float cutoffHighpassMin       = 1000.f;
        const float cutoffHighpassMax       = 5000.f;
        const float cutoffHighpassIncrement = 1.f;
        const float cutoffHighpassSkew      = 0.3f;
        
        const float defaultWetMix           = 50.f;
        const float defaultCuttoffLowpass   = 150.f;
        const float defaultCutoffHighpass   = 5000.f;

        }

        namespace Identifiers {
        
        const std::string reverbWetMixID        = "Reverb_Mix";
        const std::string reverbLowpassID       = "Reverb_Cutoff_Lowpass";
        const std::string reverbHighpassID      = "Reverb_Cutoff_Highpass";
        
        const std::string reverbWetMix1         = "wet_mix_1";
        const std::string reverbWetMix2         = "wet_mix_2";
        const std::string reverbWetMix3         = "wet_mix_3";
        const std::string reverbWetMix4         = "wet_mix_4";

        const std::string reverbCutoffLowpass1  = "cutoff_low_1";
        const std::string reverbCutoffLowpass2  = "cutoff_low_2";
        const std::string reverbCutoffLowpass3  = "cutoff_low_3";
        const std::string reverbCutoffLowpass4  = "cutoff_low_4";

        const std::string reverbCutoffHighpass1 = "cutoff_high_1";
        const std::string reverbCutoffHighpass2 = "cutoff_high_2";
        const std::string reverbCutoffHighpass3 = "cutoff_high_3";
        const std::string reverbCutoffHighpass4 = "cutoff_high_4";

        }

    }

    namespace Distortion {

        namespace Numeric {

        const float minGainDecibels         = -64.f;
        const float maxGainDecibels         = 10.f;
        const float gainIncrement           = 0.5f;
        const float gainskew                = 1.f;
        
        const float minLevel                = 0.1f;
        const float maxLevel                = 1.f;
        const float levelIncrement          = 0.01f;
        const float levelSkew               = 1.f;
        
        const float minTone                 = 0.1f;
        const float maxTone                 = 1.f;
        const float toneIncrement           = 0.01f;
        const float toneSkew                = 1.f;
        
        const float defaultGainDecibels     = 0.f;
        const float defaultLevel            = 1.f;
        const float defaultTone             = 1.f;

        }

        namespace Identifiers {
        
        const std::string distortionGainID  = "Distortion_Gain";
        const std::string distortionLevelID = "Distortion_Level";
        const std::string distortionToneID  = "Distortion_Tone";

        const std::string distortionGain1   = "gain_1";
        const std::string distortionGain2   = "gain_2";
        const std::string distortionGain3   = "gain_3";
        const std::string distortionGain4   = "gain_4";

        const std::string distortionLevel1  = "level_1";
        const std::string distortionLevel2  = "level_2";
        const std::string distortionLevel3  = "level_3";
        const std::string distortionLevel4  = "level_4";

        const std::string distortionTone1   = "tone_1";
        const std::string distortionTone2   = "tone_2";
        const std::string distortionTone3   = "tone_3";
        const std::string distortionTone4   = "tone_4";

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
        
        const std::string envelopeFilterQualityID           = "Envelope_Filter_Quality";
        const std::string envelopeFilterSensitivityID       = "Envelope_Filter_Sensitivity";
        const std::string envelopeFilterCutoffThresholdID   = "Envelope_Filter_Cutoff_Threshold";

        const std::string envelopeFilterQuality1            = "quality_1";
        const std::string envelopeFilterQuality2            = "quality_2";
        const std::string envelopeFilterQuality3            = "quality_3";
        const std::string envelopeFilterQuality4            = "quality_4";

        const std::string envelopeFilterSensitivity1        = "sensitivity_1";
        const std::string envelopeFilterSensitivity2        = "sensitivity_2";
        const std::string envelopeFilterSensitivity3        = "sensitivity_3";
        const std::string envelopeFilterSensitivity4        = "sensitivity_4";
        
        const std::string envelopeFilterCutoffThreshold1    = "cutoff_threshold_1";
        const std::string envelopeFilterCutoffThreshold2    = "cutoff_threshold_2";
        const std::string envelopeFilterCutoffThreshold3    = "cutoff_threshold_3";
        const std::string envelopeFilterCutoffThreshold4    = "cutoff_threshold_4";

        }

    }

}
