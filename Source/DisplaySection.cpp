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
DisplaySection::DisplaySection(FootprintAudioProcessor& p)
: audioProcessor(p)
{
    startTimerHz(120);
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(inputWaveform);
    addAndMakeVisible(outputWaveform);
    
    inputWaveform.setRepaintRate(60);
    inputWaveform.setBufferSize(1024);
    outputWaveform.setRepaintRate(60);
    outputWaveform.setBufferSize(1024);
    
    addAndMakeVisible(WaveformZoom);
    addAndMakeVisible(dBGridIn);
    addAndMakeVisible(dBGridOut);

    WaveformZoom.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    WaveformZoom.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);

    WaveformZoom.setColour(juce::Slider::backgroundColourId, juce::Colours::white.withAlpha(0.5f));
    WaveformZoom.setColour(juce::Slider::trackColourId, juce::Colours::lightblue);
    WaveformZoom.setColour(juce::Slider::thumbColourId, juce::Colours::white);

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

void DisplaySection::timerCallback() {
    
    juce::AudioBuffer<float> inputBuffer, outputBuffer;
    bool pullStatusIn = audioProcessor.guiFifoInput.pull(inputBuffer);
    bool pullStatusOut = audioProcessor.guiFifoOutput.pull(outputBuffer);
    if (pullStatusIn) inputWaveform.pushBuffer(inputBuffer);
    if (pullStatusOut) outputWaveform.pushBuffer(outputBuffer);
}

void DisplaySection::paint (juce::Graphics& g)
{
    g.drawImage(displayBackground, getLocalBounds().toFloat(), juce::RectanglePlacement::stretchToFit);    
    g.setColour(juce::Colours::white.withAlpha(0.5f));
    g.drawRoundedRectangle(140, 18, 500, 100, 10, 2);
    g.drawRoundedRectangle(140, 125, 500, 100, 10, 2);

    juce::Font labelFont;

    g.setColour(juce::Colours::white);
    juce::Font font;
    font.setTypefaceName("Futura");
    font.setHeight(GUIAttributes::DisplayFontSizes::h2);
    g.setFont(font); // Set the updated font
    g.drawText("Zoom", 639, 75, 40, 210, juce::Justification::centred);
    g.drawText("In", 30, 118, 40, 210, juce::Justification::centred);
    g.drawText("Out", 91, 118, 40, 210, juce::Justification::centred);
    font.setHeight(GUIAttributes::DisplayFontSizes::h3);
    g.setFont(font); // Set the updated font
    g.drawText("Peak RMS", 17, 19, 100, 10, juce::Justification::centred);

    g.setColour(juce::Colours::black.brighter());
    juce::Line<float> vLine (juce::Point<float>((getLocalBounds().getX()) + 130.f, getLocalBounds().getY() + 30.f), juce::Point<float>((getLocalBounds().getX()) + 130.f, getLocalBounds().getY() + 220.f));
    g.drawLine(vLine, 2.0f);
}

void DisplaySection::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    inputWaveform.setBounds(140, 18, 500, 100);
    outputWaveform.setBounds(140, 125, 500, 100);
    dBGridIn.setBounds(7, 37, 45, 180);
    dBGridOut.setBounds(67, 37, 45, 180);
    WaveformZoom.setBounds(639, 75, 40, 100);

    inputWaveform.setColours(juce::Colours::transparentBlack, juce::Colours::white);
    outputWaveform.setColours(juce::Colours::transparentBlack, juce::Colours::white);

}
