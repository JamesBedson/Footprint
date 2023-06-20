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
    addAndMakeVisible(dBGrid);
    addAndMakeVisible(levelInMeterLeft);
    addAndMakeVisible(levelInMeterRight);
    addAndMakeVisible(levelOutMeterLeft);
    addAndMakeVisible(levelOutMeterRight);

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

    levelInMeterLeft.setLevel(audioProcessor.getInRmsValue(0));
    levelInMeterRight.setLevel(audioProcessor.getInRmsValue(1));

    levelOutMeterLeft.setLevel(audioProcessor.getOutRmsValue(0));
    levelOutMeterRight.setLevel(audioProcessor.getOutRmsValue(1));

    levelInMeterLeft.repaint();
    levelInMeterRight.repaint();
    levelOutMeterLeft.repaint();
    levelOutMeterRight.repaint();
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
    font.setHeight(GUIAttributes::DisplayFontSizes::h5);
    g.setFont(font); // Set the updated font
    g.drawText("_", 639, 65, 40, 210, juce::Justification::centred);
    font.setHeight(GUIAttributes::DisplayFontSizes::h6);
    g.setFont(font); // Set the updated font
    g.drawText("+", 639, 25, 40, 100, juce::Justification::centred);
    font.setHeight(GUIAttributes::DisplayFontSizes::h2);
    g.setFont(font); // Set the updated font
    g.drawText("In", 17, 118, 40, 210, juce::Justification::centred);
    g.drawText("Out", 85, 118, 40, 210, juce::Justification::centred);
    font.setHeight(GUIAttributes::DisplayFontSizes::h3);
    g.setFont(font); // Set the updated font
    g.drawText("Peak RMS", 17, 19, 100, 10, juce::Justification::centred);

    g.setColour(juce::Colours::black.brighter());
    juce::Line<float> vLine (juce::Point<float>(levelMeterVLine, getLocalBounds().getY() + 30.f), juce::Point<float>(levelMeterVLine, getLocalBounds().getY() + 220.f));
    g.drawLine(vLine, 2.0f);
}

void DisplaySection::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    juce::Rectangle<int> bounds = getLocalBounds();
    inputWaveform.setBounds(140, 18, 500, 100);
    outputWaveform.setBounds(140, 125, 500, 100);
    dBGrid.setBounds(47, 45, 45, 167);
    WaveformZoom.setBounds(639, 75, 40, 100);

    inputWaveform.setColours(juce::Colours::transparentBlack, juce::Colours::white);
    outputWaveform.setColours(juce::Colours::transparentBlack, juce::Colours::white);

    float m = 60.f; //out displacement
    
    const int distanceOuterToBounds         = bounds.getWidth() * 0.04f;
    const int levelMeterHeight              = bounds.getHeight() * 0.655f;
    const int levelMeterWidth               = bounds.getWidth() * 0.013f;
    const int distanceLRChannel             = bounds.getWidth() * 0.01f;
    const int levelMeterY                   = bounds.getY() + getHeight() * 0.20f;
    levelMeterLineX                         = bounds.getX() + getWidth() * 0.21f;
    levelMeterVLine                         = bounds.getX() + getWidth() * 0.19f;
    levelMeterText                          = bounds.getX() + getWidth() * 0.21f;
    
    levelInMeterLeft.setBounds(bounds.getX() + distanceOuterToBounds,
                               levelMeterY,
                               levelMeterWidth,
                               levelMeterHeight);
    
    levelInMeterRight.setBounds(levelInMeterLeft.getRight() + distanceLRChannel,
                                levelMeterY,
                                levelMeterWidth,
                                levelMeterHeight);

    levelOutMeterRight.setSize(levelMeterWidth, levelMeterHeight);
    levelOutMeterRight.setTopRightPosition(levelMeterLineX - distanceOuterToBounds, levelMeterY);
    
    levelOutMeterLeft.setSize(levelMeterWidth, levelMeterHeight);
    levelOutMeterLeft.setTopRightPosition(levelOutMeterRight.getX() - distanceLRChannel, levelMeterY);
    
}
