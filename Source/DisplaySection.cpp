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
    bufferSizeView.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    bufferSizeView.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    bufferSizeView.onValueChange = [this](){
        if ( (1025 > int(bufferSizeView.getValue()*120)) && (int(bufferSizeView.getValue()*120) > 32) ){
            inputWaveform.setBufferSize(int(bufferSizeView.getValue()*120));
            outputWaveform.setBufferSize(int(bufferSizeView.getValue()*120));
        }
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
    g.setFont (20.0f);

    //g.drawText ("Display Section", getLocalBounds(), juce::Justification::centred, true);   // draw some placeholder text
}

void DisplaySection::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    inputWaveform.setBounds(140, 18, 500, 100);
    outputWaveform.setBounds(140, 125, 500, 100);
    
    
    bufferSizeView.setBounds(640, 75, 40, 100);

}
