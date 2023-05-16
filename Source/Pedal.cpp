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
    bypassSwitch.setLookAndFeel(&pedalLookAndFeel);
    bypassSwitch.addListener(this);
}

Pedal::~Pedal()
{
    bypassSwitch.setLookAndFeel(nullptr);
}

void Pedal::paint (juce::Graphics& g)
{
    paintBackground(g);
    juce::Rectangle<float> led;
    led.setSize(7, 7);
    led.setCentre(sliderCol2CentreX, bypassSwitch.getBounds().getY() - 0.08f * getHeight());
    if (bypassSwitch.isMouseButtonDown())
    {
        g.setColour(juce::Colours::red);
    }
    g.fillEllipse(led);
    paintAdditionalComponents(g);
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

void Pedal::buttonClicked(juce::Button* button)
{
    if (button == &bypassSwitch)
    {
        repaint();
    }
}

void Pedal::setSlot(int slot){
    
    jassert(slot >= 1 and slot <= 4);
    this->slot = slot;
}
