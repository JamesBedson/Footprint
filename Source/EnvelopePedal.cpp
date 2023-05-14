/*
  ==============================================================================

    EnvelopePedal.cpp
    Created: 14 May 2023 10:43:40am
    Author:  James Bedson

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EnvelopePedal.h"

//==============================================================================
EnvelopePedal::EnvelopePedal()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

EnvelopePedal::~EnvelopePedal()
{
}

void EnvelopePedal::paint (juce::Graphics& g)
{

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    juce::Rectangle<int> textBounds = getLocalBounds().withY(getHeight() * -0.4f); // Adjust the vertical position here
    g.drawText ("EnvelopePedal", textBounds,
                juce::Justification::centred, true);   // draw some placeholder text
}

void EnvelopePedal::resizeChild(){
    
}
