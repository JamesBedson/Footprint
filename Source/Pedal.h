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
//#include "DeleteSwitchLookandFeel.h"
#include "GUIAttributes.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/

using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

class Pedal : public juce::Component, public juce::Button::Listener
{
public:
    Pedal();
    ~Pedal()                                            override;

    void paint (juce::Graphics&)                        override;
    void resized()                                      override;
    
    virtual void paintBackground(juce::Graphics&) = 0;
    virtual void paintAdditionalComponents(juce::Graphics&) = 0;
    virtual void resizeChild() = 0;

    void buttonClicked(juce::Button* button)            override;
    void mouseEnter(const juce::MouseEvent& event)      override;
    void mouseExit(const juce::MouseEvent& event)       override;
    void setSlot(int slot);
    bool isDeleted();

protected:
    
    int sliderCol1CentreX;
    int sliderCol2CentreX;
    int sliderCol3CentreX;
    
    int sliderRow1CentreY;
    int sliderRow2CentreY;
    int sliderRow3CentreY;

    int sliderWidth, sliderHeight;
    int sliderLabelWidth, sliderLabelHeight;
    
    juce::ToggleButton  bypassSwitch;
    juce::ToggleButton  deleteSwitch;
    PedalLookAndFeel    pedalLookAndFeel;
    //DeleteSwitchLookandFeel deleteSwitchLookandFeel;
    
    juce::Image         backgroundSlot1 = juce::ImageCache::getFromMemory(BinaryData::Slot1PurpleBlue_png, BinaryData::Slot2PurpleBlue_pngSize);
    juce::Image         backgroundSlot2 = juce::ImageCache::getFromMemory(BinaryData::Slot2PurpleBlue_png, BinaryData::Slot2PurpleBlue_pngSize);
    juce::Image         backgroundSlot3 = juce::ImageCache::getFromMemory(BinaryData::Slot3PurpleBlue_png, BinaryData::Slot3PurpleBlue_pngSize);
    
    int slot = 0;

    bool isInside = true;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Pedal)
};
