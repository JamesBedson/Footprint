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
    
    juce::Rectangle<int> topLeft, topRigth, bottomLeft, bottomRigth, bypass;
    auto rectWidth = 10;
    auto rectHeight = 10;
    
    topLeft.setSize(rectWidth, rectHeight);
    topLeft.setCentre(sliderCol1CentreX, sliderRow1CentreY);
    
    topRigth.setSize(rectWidth, rectHeight);
    topRigth.setCentre(sliderCol3CentreX, sliderRow1CentreY);
    
    bottomLeft.setSize(rectWidth, rectHeight);
    bottomLeft.setCentre(sliderCol1CentreX, sliderRow2CentreY);
    
    bottomRigth.setSize(rectWidth, rectHeight);
    bottomRigth.setCentre(sliderCol3CentreX, sliderRow2CentreY);
    
    g.setColour(juce::Colours::white);
    g.drawEllipse(topLeft.toFloat(), 1.5f);
    
    g.setColour(juce::Colours::red);
    g.drawEllipse(topRigth.toFloat(), 1.5f);
    
    g.setColour(juce::Colours::blue);
    g.drawEllipse(bottomLeft.toFloat(), 1.5f);
    
    g.setColour(juce::Colours::green);
    g.drawEllipse(bottomRigth.toFloat(), 1.5f);
    
    juce::Rectangle<float> led;
    led.setSize(7, 7);
    led.setCentre(sliderCol2CentreX, bypassSwitch.getBounds().getY() - 0.08f * getHeight());
    g.fillEllipse(led);
}

void ReverbPedal::resized()
{
    auto bounds         = getBounds();
    auto width          = getWidth();
    auto height         = getHeight();
    sliderCol1CentreX   = getX() + width * 0.2f;
    sliderRow1CentreY   = getY() + height * 0.2f;
    sliderCol3CentreX   = getX() + width * 0.8f;
    sliderCol2CentreX   = bounds.getCentreX();

    sliderRow2CentreY   = bounds.getCentreY();
    
    auto buttonWidth    = 20;
    auto buttonHeight   = 20;
    bypassSwitch.setSize(buttonWidth, buttonHeight);
    bypassSwitch.setCentrePosition(bounds.getCentreX(), bounds.getCentreY() + width * 0.6f);

}
