/*
  ==============================================================================

    Pedal.h
    Created: 14 May 2023 10:42:34am
    Author:  James Bedson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PedalLookAndFeel.h"

//==============================================================================
/*
*/
class Pedal  : public juce::Component, public juce::Button::Listener
{
public:
    Pedal();
    ~Pedal()                                            override;

    void paint (juce::Graphics&)                        override;
    void resized()                                      override;
    
    virtual void paintChild(juce::Graphics&) = 0;
    virtual void resizeChild() = 0;

    void buttonClicked(juce::Button* button)            override;

protected:
    
    int sliderCol1CentreX;
    int sliderCol2CentreX;
    int sliderCol3CentreX;
    
    int sliderRow1CentreY;
    int sliderRow2CentreY;
    int sliderRow3CentreY;

    int sliderWidth, sliderHeight;
    int sliderLabelWidth, sliderLabelHeight;
    
    juce::ToggleButton bypassSwitch;
    PedalLookAndFeel pedalLookAndFeel;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Pedal)
};
