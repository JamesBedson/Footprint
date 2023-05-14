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
    addAndMakeVisible(pedal);
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
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (juce::Colours::darkred);   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PedalSection", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
    
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
