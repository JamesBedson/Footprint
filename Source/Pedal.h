/*
  ==============================================================================

    Pedal.h
    Created: 14 May 2023 10:42:34am
    Author:  James Bedson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Pedal  : public juce::Component
{
public:
    Pedal();
    ~Pedal() override;

    void paint (juce::Graphics&) override;
    void resized() override;

protected:
    
    int sliderCol1CentreX;
    int sliderCol2CentreX;
    int sliderCol3CentreX;
    
    int sliderRow1CentreY;
    int sliderRow2CentreY;
    int sliderRow3CentreY;
    
    
    juce::TextButton bypassSwitch;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Pedal)
    
    
    
};