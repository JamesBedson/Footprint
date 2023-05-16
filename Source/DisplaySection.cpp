/*
  ==============================================================================

    DisplaySection.cpp
    Created: 6 May 2023 2:11:16pm
    Author:  James Bedson

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DisplaySection.h"

//==============================================================================
DisplaySection::DisplaySection()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

DisplaySection::~DisplaySection()
{
}

void DisplaySection::paint (juce::Graphics& g)
{
    g.drawImage(displayBackground, getLocalBounds().toFloat(), juce::RectanglePlacement::stretchToFit);
    
    /*
    g.setColour(juce::Colours::salmon);
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 15.0f, 1.0f);
    g.setColour(juce::Colours::salmon);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 15.0f);*/
    g.setColour(juce::Colours::white);
    g.setFont (20.0f);

    g.drawText ("Display Section", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void DisplaySection::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
