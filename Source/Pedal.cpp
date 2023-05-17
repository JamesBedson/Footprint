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
    if (isInside)
    {
        auto bounds = getLocalBounds().reduced(6.0f, 6.0f);
        g.setColour(juce::Colours::white.darker());
        g.drawRoundedRectangle(bounds.toFloat(), 10.0f, 1.0f);
        g.setColour(juce::Colours::black);

    }

    juce::Rectangle<float> led;
    led.setSize(7, 7);
    led.setCentre(sliderCol2CentreX, bypassSwitch.getBounds().getY() - 0.08f * getHeight());
    if (bypassSwitch.getToggleState())
    {
        g.setColour(juce::Colours::darkorange);
    }
    g.fillEllipse(led);
    g.setColour(juce::Colours::white);
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

void Pedal::mouseMove(const juce::MouseEvent& event)
{
    isInside = true;
    repaint();
}

void Pedal::mouseExit(const juce::MouseEvent& event)
{
    isInside = false;
    repaint();
}

void Pedal::setSlot(int slot){
    
    jassert(slot >= 1 & slot <= 4);
    this->slot = slot;
}