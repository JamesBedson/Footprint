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
    for (auto& slider : sliders){
        addAndMakeVisible(slider);
        slider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        slider->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0,0);
    }
    type.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
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
    juce::Rectangle<int> textBounds = getLocalBounds().withY(getHeight() * -0.4f); // Adjust the vertical position here
    g.drawText ("ReverbPedal", textBounds,
                juce::Justification::centred, true);   // draw some placeholder text


    
    juce::Rectangle<float> led;
    led.setSize(7, 7);
    led.setCentre(sliderCol2CentreX, bypassSwitch.getBounds().getY() - 0.08f * getHeight());
    g.fillEllipse(led);
    
    
}

void ReverbPedal::resizeChild(){
    
    for (auto& slider : sliders){
        if (slider != &type){
            slider->setSize(sliderWidth, sliderHeight);
        }
        else type.setSize(150, 50);
    }
    
    mix.setCentrePosition       (sliderCol2CentreX, sliderRow2CentreY);
    highCut.setCentrePosition   (sliderCol3CentreX, sliderRow1CentreY);
    lowCut.setCentrePosition    (sliderCol1CentreX, sliderRow1CentreY);
    type.setCentrePosition      (sliderCol2CentreX, sliderRow3CentreY);
    
}
