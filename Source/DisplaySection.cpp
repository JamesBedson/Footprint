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
    
    inputWaveform.setRepaintRate(60);
    inputWaveform.setBufferSize(1024);
    outputWaveform.setRepaintRate(60);
    outputWaveform.setBufferSize(1024);
    
    addAndMakeVisible(WaveformZoom);
        
    WaveformZoom.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    WaveformZoom.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    WaveformZoom.onValueChange = [this](){
        float sliderValue = WaveformZoom.getValue();
        
        sliderValue = sliderValue * -1 + 10.f;
        
        if ( (1025 > int(sliderValue*120)) && (int(sliderValue*120) > 32) ){
            inputWaveform.setBufferSize(int(sliderValue*120));
            outputWaveform.setBufferSize(int(sliderValue*120));
        }
    };
    
    inputWaveform.setColours(juce::Colours::white, juce::Colours::black);
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
    
    g.setColour(juce::Colours::white.withAlpha(0.5f));
    g.drawRoundedRectangle(140, 18, 500, 100, 10, 2);
    g.drawRoundedRectangle(140, 125, 500, 100, 10, 2);

    
    g.setColour(juce::Colours::white);
    juce::Font font(12.8f);
    font.setTypefaceName("Futura");
    font.setBold(false);
    g.setFont(font); // Set the updated font
    g.drawText("Zoom", 639, 75, 40, 210, juce::Justification::centred);
}

void DisplaySection::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    inputWaveform.setBounds(140, 18, 500, 100);
    outputWaveform.setBounds(140, 125, 500, 100);
    
    
    WaveformZoom.setBounds(639, 75, 40, 100);

}
