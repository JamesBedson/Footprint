/*
  ==============================================================================

    ReverbPedal.h
    Created: 14 May 2023 10:42:54am
    Author:  James Bedson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Pedal.h"
#include "PedalLookAndFeel.h"

//==============================================================================
/*
*/
class ReverbPedal  : public Pedal
{
public:
    ReverbPedal();
    ~ReverbPedal()                  override;

<<<<<<< HEAD
    void paint (juce::Graphics&)    override;
    void resizeChild()              override;
=======
    void paint (juce::Graphics&) override;
    void resizeChild() override;
>>>>>>> main


private:

    juce::Slider mix, highCut, lowCut;
    std::vector<juce::Slider*> sliders {&mix, &highCut, &lowCut};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbPedal)
};
