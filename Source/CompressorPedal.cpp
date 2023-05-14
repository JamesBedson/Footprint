/*
  ==============================================================================

    CompressorPedal.cpp
    Created: 14 May 2023 10:42:45am
    Author:  James Bedson

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CompressorPedal.h"

//==============================================================================
CompressorPedal::CompressorPedal()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

CompressorPedal::~CompressorPedal()
{
}

void CompressorPedal::paint (juce::Graphics& g)
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
    juce::Rectangle<int> textBounds = getLocalBounds().withY(getHeight() * -0.4f); // Adjust the vertical position here
    g.drawText ("CompressorPedal", textBounds,
                juce::Justification::centred, true);   // draw some placeholder text

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
