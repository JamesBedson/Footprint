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
    bypassSwitch.setLookAndFeel(&buttonLookAndFeel);
    
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
    
    sliderCol3CentreX   = getX() + width * 0.8f;
    sliderCol2CentreX   = bounds.getCentreX();
    sliderRow2CentreY   = bounds.getCentreY();
    
    sliderRow3CentreY   = bounds.getCentreY() + 53;
    
    auto buttonWidth    = 20;
    auto buttonHeight   = 20;
    
    sliderWidth         = 60;
    sliderHeight        = 60;
    
    sliderLabelWidth    = sliderWidth;
    sliderLabelHeight   = 15;
    bypassSwitch.setSize(buttonWidth, buttonHeight);
    bypassSwitch.setCentrePosition(bounds.getCentreX(), bounds.getCentreY() + width * 0.6f);
    
    resizeChild();

}
