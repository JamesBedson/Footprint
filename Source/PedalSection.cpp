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
    
    addAndMakeVisible(compressorPedal);
    addAndMakeVisible(reverbPedal);
    addAndMakeVisible(envelopePedal);
    addAndMakeVisible(distortionPedal);
    

}

PedalSection::~PedalSection()
{
}

void PedalSection::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::white.darker().darker());
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 15.0f, 1.0f);
    g.setColour(juce::Colours::transparentBlack);
    //g.fillRoundedRectangle(getLocalBounds().toFloat(), 15.0f);
    g.setFont (14.0f);
    g.setColour(juce::Colours::white);
    juce::Line<float> line1 (juce::Point<float>((getLocalBounds().getWidth() * 0.25f) - 17.0f, getLocalBounds().getHeight() * 0.5f), juce::Point<float>((getLocalBounds().getWidth() * 0.25f) + 20.0f, getLocalBounds().getHeight() * 0.5f));
    juce::Line<float> line2(juce::Point<float>((getLocalBounds().getWidth() * 0.5f) - 17.0f, getLocalBounds().getHeight() * 0.5f), juce::Point<float>((getLocalBounds().getWidth() * 0.5f) + 20.0f, getLocalBounds().getHeight() * 0.5f));
    juce::Line<float> line3(juce::Point<float>((getLocalBounds().getWidth() * 0.75f) - 17.0f, getLocalBounds().getHeight() * 0.5f), juce::Point<float>((getLocalBounds().getWidth() * 0.75f) + 20.0f, getLocalBounds().getHeight() * 0.5f));
    juce::Line<float> line4(juce::Point<float>((getLocalBounds().getWidth()) - 17.0f, getLocalBounds().getHeight() * 0.5f), juce::Point<float>((getLocalBounds().getWidth()) + 50.0f, getLocalBounds().getHeight() * 0.5f));
    g.drawLine(line1, 2.0f);
    g.drawLine(line2, 2.0f);
    g.drawLine(line3, 2.0f);
    g.drawLine(line4, 2.0f);
}

void PedalSection::resized()
{
    juce::Rectangle<int> bounds(getLocalBounds().getX(), getLocalBounds().getY(), getLocalBounds().getWidth(), getLocalBounds().getHeight());
    
    compressorPedal.setSlot(1);
    distortionPedal.setSlot(2);
    reverbPedal.setSlot(3);
    envelopePedal.setSlot(4);
    
    compressorPedal.setSize(200, 300);
    compressorPedal.setCentrePosition(bounds.getX() + getWidth() * 0.25f - compressorPedal.getWidth() * 0.58f, bounds.getCentreY());

    distortionPedal.setSize(200, 300);
    distortionPedal.setCentrePosition(bounds.getX() + getWidth() * 0.5f - distortionPedal.getWidth() * 0.58f, bounds.getCentreY());
    
    reverbPedal.setSize(200, 300);
    reverbPedal.setCentrePosition(bounds.getX() + getWidth() * 0.75f - reverbPedal.getWidth() * 0.58f, bounds.getCentreY());
    
    envelopePedal.setSize(200, 300);
    envelopePedal.setCentrePosition(bounds.getX() + getWidth() - envelopePedal.getWidth() * 0.58f, bounds.getCentreY());
}
