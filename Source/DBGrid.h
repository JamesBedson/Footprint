/*
  ==============================================================================

    DBGrid.h
    Created: 12 Jun 2023 6:49:06pm
    Author:  Iker

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "GUIAttributes.h"

class DBGrid: public juce::Component
{
public:
    DBGrid();
    ~DBGrid() override;

    void paint(juce::Graphics& g) override;
    void resized()                override;
    juce::Array<float> getPositions();


private:
    juce::Array<float> dbValues = {6.f, 3.f, 0.f, -3.f, -12.f, -24.f, -48.f, -60.f};
    //juce::Array<float> dbValues = {6.f ,0.f, -6.f, -12.f, -18.f, -24.f, -30.f, -36.f, -42.f, -60.f};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DBGrid)
};