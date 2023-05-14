/*
  ==============================================================================

    PedalLookAndFeel.cpp
    Created: 14 May 2023 10:43:50am
    Author:  James Bedson

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PedalLookAndFeel.h"

//==============================================================================
PedalLookAndFeel::PedalLookAndFeel()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::red);

}

PedalLookAndFeel::~PedalLookAndFeel()
{
}

void PedalLookAndFeel::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PedalLookAndFeel", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PedalLookAndFeel::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
