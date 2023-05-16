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
    addAndMakeVisible(CompressorPedal);
    addAndMakeVisible(ReverbPedal);
    addAndMakeVisible(EnvelopePedal);
    addAndMakeVisible(DistortionPedal);

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
    
    CompressorPedal.setSize(200, 300);
    CompressorPedal.setCentrePosition(bounds.getX() + getWidth() * 0.25f - CompressorPedal.getWidth() * 0.58f, bounds.getCentreY());

    DistortionPedal.setSize(200, 300);
    DistortionPedal.setCentrePosition(bounds.getX() + getWidth() * 0.5f - DistortionPedal.getWidth() * 0.58f, bounds.getCentreY());

    ReverbPedal.setSize(200, 300);
    ReverbPedal.setCentrePosition(bounds.getX() + getWidth() * 0.75f - ReverbPedal.getWidth() * 0.58f, bounds.getCentreY());

    EnvelopePedal.setSize(200, 300);
    EnvelopePedal.setCentrePosition(bounds.getX() + getWidth() - EnvelopePedal.getWidth() * 0.58f, bounds.getCentreY());
}
