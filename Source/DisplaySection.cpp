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
    addAndMakeVisible(inputWaveform);
    addAndMakeVisible(outputWaveform);
    
    inputWaveform.setRepaintRate(40);
    inputWaveform.setBufferSize(256);
    outputWaveform.setRepaintRate(40);
    outputWaveform.setBufferSize(256);
    
    addAndMakeVisible(bufferSizeView);
    bufferSizeView.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    bufferSizeView.onValueChange = [this](){
        inputWaveform.setBufferSize(int(bufferSizeView.getValue())*120);
        outputWaveform.setBufferSize(int(bufferSizeView.getValue())*120);
    };
    
    inputWaveform.setColours(juce::Colours::white.withBrightness(0.5f), juce::Colours::black);
    outputWaveform.setColours(juce::Colours::white, juce::Colours::black);
    
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
    juce::Font font(20.0f);
    font.setTypefaceName("Arial");
    font.setBold(true);
    g.setFont(font); // Set the updated font

    g.drawText ("Display Section", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void DisplaySection::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    inputWaveform.setBounds(140, 18, 500, 100);
    outputWaveform.setBounds(140, 125, 500, 100);
    
    
    bufferSizeView.setBounds(900, 155, 400, 100);

}
