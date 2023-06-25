/*
  ==============================================================================

    GUIAttributes.h
    Created: 22 May 2023 6:28:49pm
    Author:  Iker

  ==============================================================================
*/

#pragma once
namespace GUIAttributes {
    namespace PedalFontSizes {
        const int h1 = 20; //Titles
        const int h2 = 17; //Sliders
        const int h3 = 22; //Reverb Type Information
    }
    namespace ControlFontSizes {
        const int h1 = 50; //Titles
        const int h2 = 18; //Sliders
    }
    namespace DisplayFontSizes {
        const int h1 = 20; //Titles
        const int h2 = 17; //Sliders
        const int h3 = 19; //Title v2
        const int h4 = 13; //RMS GRID
        const int h5 = 15; //- Zoom
        const int h6 = 20; //+ Zoom
        const int h7 = 13; //dB Max Value
        const int h8 = 8; //dB Min Value
    }
    namespace LevelMeterRange {
        const float minLMR = -60.f;                 //Min Level Meter Range
        const float maxLMR = 6.f;                   //Max Level Meter Range
    }
}
