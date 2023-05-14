/*
  ==============================================================================

    Pedal.cpp
    Created: 14 May 2023 10:42:34am
    Author:  James Bedson

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Pedal.h"

//==============================================================================
Pedal::Pedal()
{
    addAndMakeVisible(bypassSwitch);

}

Pedal::~Pedal()
{
}

void Pedal::paint (juce::Graphics& g)
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
    
    juce::Rectangle<int> col1Row1, col2Row2, col3Row1, col1Row2, col3Row2;
    auto rectWidth = 10;
    auto rectHeight = 10;
    
    col1Row1.setSize(rectWidth, rectHeight);
    col1Row1.setCentre(sliderCol1CentreX, sliderRow1CentreY);
    
    /*col2Row2.setSize(rectWidth, rectHeight);
    col2Row2.setCentre(sliderCol2CentreX, sliderRow2CentreY);*/
    
    col3Row1.setSize(rectWidth, rectHeight);
    col3Row1.setCentre(sliderCol3CentreX, sliderRow1CentreY);
    
    col3Row2.setSize(rectWidth, rectHeight);
    col3Row2.setCentre(sliderCol3CentreX, sliderRow2CentreY);
    
    col1Row2.setSize(rectWidth, rectHeight);
    col1Row2.setCentre(sliderCol1CentreX, sliderRow2CentreY);
    
    g.setColour(juce::Colours::red);
    g.drawEllipse(col1Row1.toFloat(), 1.5f);
    
    g.setColour(juce::Colours::red);
    g.drawEllipse(col3Row1.toFloat(), 1.5f);
    
    g.setColour(juce::Colours::red);
    g.drawEllipse(col1Row2.toFloat(), 1.5f);
    
    g.setColour(juce::Colours::red);
    g.drawEllipse(col3Row2.toFloat(), 1.5f);
    
    juce::Rectangle<float> led;
    led.setSize(7, 7);
    led.setCentre(sliderCol2CentreX, bypassSwitch.getBounds().getY() - 0.08f * getHeight());
    g.fillEllipse(led);
    
    
}

void Pedal::resized()
{
    auto bounds         = getBounds();
    auto width          = getWidth();
    auto height         = getHeight();
    sliderCol1CentreX   = getX() + width * 0.2f;
    sliderRow1CentreY   = getY() + height * 0.2f;
    auto topRight       = bounds.getTopRight();
    sliderCol3CentreX   = getX() + width * 0.8f;
    sliderCol2CentreX   = bounds.getCentreX();
    sliderRow2CentreY   = bounds.getCentreY();
    
    auto buttonWidth    = 20;
    auto buttonHeight   = 20;
    bypassSwitch.setSize(buttonWidth, buttonHeight);
    bypassSwitch.setCentrePosition(bounds.getCentreX(), bounds.getCentreY() + width * 0.6f);


}
