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
