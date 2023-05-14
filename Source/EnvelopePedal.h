/*
  ==============================================================================

    EnvelopePedal.h
    Created: 14 May 2023 10:43:40am
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
class EnvelopePedal  : public Pedal
{
public:
    EnvelopePedal();
    ~EnvelopePedal()                override;

<<<<<<< HEAD
    void paint (juce::Graphics&)    override;
    void resizeChild() override;

private:

    /*juce::Slider*/

=======
    void paint (juce::Graphics&) override;
    void resizeChild() override;
    
private:
    juce::Slider qualityFactor, sensitivity, cutoffThreshold;
    std::vector<juce::Slider*> sliders {&qualityFactor, &sensitivity, &cutoffThreshold};
    
    
>>>>>>> main
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopePedal)
};
