/*
  ==============================================================================

    DistortionPedal.cpp
    Created: 14 May 2023 10:43:31am
    Author:  James Bedson

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DistortionPedal.h"

//==============================================================================
DistortionPedal::DistortionPedal()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

DistortionPedal::~DistortionPedal()
{
}

void DistortionPedal::paint (juce::Graphics& g)
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
    g.drawText ("DistortionPedal", textBounds,
                juce::Justification::centred, true);   // draw some placeholder text

    juce::Rectangle<int> col1Row1, col2Row2, col3Row1, col1Row2, col3Row2;
    auto rectWidth = 10;
    auto rectHeight = 10;

    col1Row1.setSize(rectWidth, rectHeight);
    col1Row1.setCentre(sliderCol1CentreX, sliderRow1CentreY);

    col2Row2.setSize(rectWidth, rectHeight);
    col2Row2.setCentre(sliderCol2CentreX, sliderRow2CentreY);

    col3Row1.setSize(rectWidth, rectHeight);
    col3Row1.setCentre(sliderCol3CentreX, sliderRow1CentreY);

    g.setColour(juce::Colours::white);
    g.drawEllipse(col1Row1.toFloat(), 1.5f);

    g.setColour(juce::Colours::red);
    g.drawEllipse(col3Row1.toFloat(), 1.5f);

    g.setColour(juce::Colours::green);
    g.drawEllipse(col2Row2.toFloat(), 1.5f);

    juce::Rectangle<float> led;
    led.setSize(7, 7);
    led.setCentre(sliderCol2CentreX, bypassSwitch.getBounds().getY() - 0.08f * getHeight());
    g.fillEllipse(led);

}