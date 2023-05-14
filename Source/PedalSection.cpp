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
    
    g.drawRect(pedal.getBounds());
}

void PedalSection::resized()
{
    auto bounds = getLocalBounds();
    
    pedal.setSize(200, 300);
    pedal.setCentrePosition(bounds.getCentreX(), bounds.getCentreY());

}
