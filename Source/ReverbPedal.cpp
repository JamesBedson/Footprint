/*
  ==============================================================================

    ReverbPedal.cpp
    Created: 14 May 2023 10:42:54am
    Author:  James Bedson

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ReverbPedal.h"

//==============================================================================
ReverbPedal::ReverbPedal()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

ReverbPedal::~ReverbPedal()
{
}

void ReverbPedal::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);

    juce::Rectangle<int> textBounds = getLocalBounds().withY(getHeight() * -0.4f); // Adjust the vertical position here
    g.drawText("ReverbPedal", textBounds,
        juce::Justification::centred, true);   // draw some placeholder text
    
    juce::Rectangle<int> topLeft, topRigth, bottomCenter;
    auto rectWidth = 10;
    auto rectHeight = 10;
    
    topLeft.setSize(rectWidth, rectHeight);
    topLeft.setCentre(sliderCol1CentreX, sliderRow1CentreY);
    
    topRigth.setSize(rectWidth, rectHeight);
    topRigth.setCentre(sliderCol3CentreX, sliderRow1CentreY);
    
    bottomCenter.setSize(rectWidth, rectHeight);
    bottomCenter.setCentre(sliderCol2CentreX, sliderRow2CentreY);

    g.setColour(juce::Colours::white);
    g.drawEllipse(topLeft.toFloat(), 1.5f);
    g.fillEllipse(topLeft.toFloat());
    
    g.setColour(juce::Colours::white);
    g.drawEllipse(topRigth.toFloat(), 1.5f);
    g.fillEllipse(topRigth.toFloat());
    
    g.setColour(juce::Colours::white);
    g.drawEllipse(bottomCenter.toFloat(), 1.5f);
    g.fillEllipse(bottomCenter.toFloat());

    
    juce::Rectangle<float> led;
    led.setSize(7, 7);
    led.setCentre(sliderCol2CentreX, bypassSwitch.getBounds().getY() - 0.08f * getHeight());
    g.fillEllipse(led);
}

void ReverbPedal::resizeChild()
{
}