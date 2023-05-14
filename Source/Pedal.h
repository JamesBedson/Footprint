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
class Pedal  : public juce::Component
{
public:
    Pedal();
    ~Pedal()                            override;

<<<<<<< HEAD
    void paint (juce::Graphics&)        override;
    void resized()                      override;
=======
    void paint (juce::Graphics&) override;
    void resized() override;
>>>>>>> main
    virtual void resizeChild() = 0;

protected:
    
    int sliderCol1CentreX;
    int sliderCol2CentreX;
    int sliderCol3CentreX;
    
    int sliderRow1CentreY;
    int sliderRow2CentreY;
    int sliderRow3CentreY;
<<<<<<< HEAD

=======
    
>>>>>>> main
    int sliderWidth, sliderHeight;
        
    juce::TextButton bypassSwitch;
    PedalLookAndFeel lookAndFeel;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Pedal)
};
