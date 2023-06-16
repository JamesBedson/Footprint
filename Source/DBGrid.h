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
    juce::Array<float> getPositions();
    void resized()                override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DBGrid)
};

