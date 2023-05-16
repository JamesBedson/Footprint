/*
  ==============================================================================

    PedalSection.cpp
    Created: 6 May 2023 2:06:57pm
    Author:  James Bedson

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PedalSection.h"

//==============================================================================
PedalSection::PedalSection()
{
    
    addAndMakeVisible(compressorPedal);
    addAndMakeVisible(reverbPedal);
    addAndMakeVisible(envelopePedal);
    addAndMakeVisible(distortionPedal);
    

}

PedalSection::~PedalSection()
{
}

void PedalSection::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::white.darker().darker());
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 15.0f, 1.0f);
    g.setColour(juce::Colours::transparentBlack);
    //g.fillRoundedRectangle(getLocalBounds().toFloat(), 15.0f);
    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
}

void PedalSection::resized()
{
    auto bounds = getLocalBounds();
    
    compressorPedal.setSlot(1);
    distortionPedal.setSlot(2);
    reverbPedal.setSlot(3);
    envelopePedal.setSlot(4);
    
    compressorPedal.setSize(200, 300);
    compressorPedal.setCentrePosition(bounds.getX() + getWidth() * 0.25f - compressorPedal.getWidth() * 0.58f, bounds.getCentreY());

    distortionPedal.setSize(200, 300);
    distortionPedal.setCentrePosition(bounds.getX() + getWidth() * 0.5f - distortionPedal.getWidth() * 0.58f, bounds.getCentreY());
    
    reverbPedal.setSize(200, 300);
    reverbPedal.setCentrePosition(bounds.getX() + getWidth() * 0.75f - reverbPedal.getWidth() * 0.58f, bounds.getCentreY());
    
    envelopePedal.setSize(200, 300);
    envelopePedal.setCentrePosition(bounds.getX() + getWidth() - envelopePedal.getWidth() * 0.58f, bounds.getCentreY());
}
