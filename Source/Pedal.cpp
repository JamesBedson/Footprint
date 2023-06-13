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
Pedal::Pedal(const int& pedalSlot)
: pedalSlot(pedalSlot)
{
    addAndMakeVisible(bypassSwitch);
    bypassSwitch.setToggleState(true, juce::dontSendNotification);
    bypassSwitch.setLookAndFeel(&pedalLookAndFeel);
    bypassSwitch.addListener(this);
    
    addAndMakeVisible(deleteSwitch);
    deleteSwitch.setLookAndFeel(&deleteSwitchLookandFeel);
    deleteSwitch.setToggleState(false, juce::dontSendNotification);
    
}

Pedal::~Pedal()
{
    bypassSwitch.setLookAndFeel(nullptr);
    deleteSwitch.setLookAndFeel(nullptr);
}

void Pedal::paint (juce::Graphics& g)
{
    paintBackground(g);

    if (isMouseOver(true))
    {
        auto bounds = getLocalBounds().reduced(6.0f, 6.0f);
        g.setColour(juce::Colours::white.darker());
        g.drawRoundedRectangle(bounds.toFloat(), 10.0f, 1.0f);
        g.setColour(juce::Colours::black);
    }

    juce::Rectangle<float> led;
    led.setSize(7, 7);
    led.setCentre(sliderCol2CentreX, bypassSwitch.getBounds().getY() - 0.05f * getHeight());
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
    auto bounds         = getLocalBounds();
    auto width          = bounds.getWidth();
    auto height         = bounds.getHeight();
    sliderCol1CentreX   = bounds.getX() + width * 0.2f;
    sliderRow1CentreY   = bounds.getY() + height * 0.2f + 22.f;
    
    sliderCol3CentreX   = bounds.getX() + width * 0.8f;
    sliderCol2CentreX   = bounds.getCentreX();
    sliderRow2CentreY   = bounds.getCentreY() + 22.f;
    
    sliderRow3CentreY   = bounds.getCentreY() + 53 + 22.f;
    
    auto buttonWidth    = 20;
    auto buttonHeight   = 20;
    
    sliderWidth         = 60;
    sliderHeight        = 60;
    
    sliderLabelWidth    = sliderWidth;
    sliderLabelHeight   = 15;
    bypassSwitch.setSize(buttonWidth, buttonHeight);
    bypassSwitch.setCentrePosition(bounds.getCentreX(), bounds.getCentreY() + width * 0.6f);
    
    deleteSwitch.setBounds(bounds.getX() + 15, bounds.getY() + 15, buttonWidth * 0.6f, buttonHeight * 0.6f);
    
    resizeChild();

}

void Pedal::buttonClicked(juce::Button* button)
{
    if (button == &bypassSwitch) {
        
        if (bypassSwitch.getToggleState() == true) {
            bypassState = false;
        }
        else {
            bypassState = true;
        }
            repaint();
    }
}

void Pedal::mouseEnter(const juce::MouseEvent& event)
{
    isInside = true;
    repaint();
}

void Pedal::mouseExit(const juce::MouseEvent& event)
{
    isInside = false;
    repaint();
}

bool Pedal::isDeleted(){
    
    return deleteSwitch.getToggleState();
}
