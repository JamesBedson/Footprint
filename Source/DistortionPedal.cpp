/*
  ==============================================================================

    DistortionPedal.cpp
    Created: 14 May 2023 10:43:31am
    Author:  James Bedson

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DistortionPedal.h"

//==============================================================================
DistortionPedal::DistortionPedal()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

DistortionPedal::~DistortionPedal()
{
}

void DistortionPedal::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("DistortionPedal", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void DistortionPedal::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
