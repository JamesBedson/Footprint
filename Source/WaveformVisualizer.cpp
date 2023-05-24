/*
  ==============================================================================

    WaveformVisualizer.cpp
    Created: 22 May 2023 10:17:19am
    Author:  Pau Segalés Torres

  ==============================================================================
*/

#include "WaveformVisualizer.h"

WaveformVisualizer::WaveformVisualizer() : juce::AudioVisualiserComponent(1)
{
    // Initialize any additional variables or settings
    setOpaque(false);    
}

WaveformVisualizer::~WaveformVisualizer()
{
    // Clean up any allocated resources
}
