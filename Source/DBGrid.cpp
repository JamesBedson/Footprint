/*
  ==============================================================================

    DBGrid.cpp
    Created: 12 Jun 2023 6:49:06pm
    Author:  Iker

  ==============================================================================
*/

#include "DBGrid.h"

DBGrid::DBGrid()
{
    setSize(100, 200); // Set the size according to your needs
}

DBGrid::~DBGrid()
{
}

void DBGrid::paint(juce::Graphics& g)
{
    //g.setColour(juce::Colours::red);
    //g.fillAll();
    juce::Rectangle<int> bounds = getLocalBounds();
    float top = bounds.getY();
    float bottom = bounds.getBottom();
    float rangeMin = GUIAttributes::LevelMeterRange::minLMR;
    float rangeMax = GUIAttributes::LevelMeterRange::maxLMR;

    juce::Array<float> normPositions;
    g.setColour(juce::Colours::white.darker().darker().darker().darker());

    for (auto value : dbValues)
    {
        float y = juce::jmap(value, rangeMin, rangeMax, top, bottom);
        normPositions.add(y);
        juce::Line<float> line{float(bounds.getX()), y, float(bounds.getRight()), y };
        //g.drawLine(line);
    }

    juce::Array<float> positions = getPositions();
    juce::Array<float> positionsRev = positions;
    std::reverse(positionsRev.begin(), positionsRev.end());

    g.setColour(juce::Colours::white.darker());
    juce::String label;
    juce::Font font;
    font.setTypefaceName("Futura");
    auto i = 0;
    for (auto value : dbValues)
    {
        if (value >= 0)
            label = "+" + juce::String(value) + "dB";
        else
            label = "-" + juce::String(-value) + "dB";

        //float fontSize = juce::jmap(std::abs(value), GUIAttributes::LevelMeterRange::maxLMR, GUIAttributes::LevelMeterRange::minLMR, float(GUIAttributes::DisplayFontSizes::h7), float(GUIAttributes::DisplayFontSizes::h8));
        float fontSize = GUIAttributes::DisplayFontSizes::h7 - i;
        font.setHeight(fontSize);
        g.setFont(font);
        //g.drawText(label, (bounds.getWidth() / 2) * 0.45f, positionsRev[i], 30, 10, juce::Justification::centred);
        i++;
    }
}

juce::Array<float> DBGrid::getPositions()
{
    juce::Rectangle<int> bounds = getLocalBounds();
    float top = bounds.getY();
    float bottom = bounds.getBottom();
    float rangeMin = GUIAttributes::LevelMeterRange::minLMR;
    float rangeMax = GUIAttributes::LevelMeterRange::maxLMR;

    juce::Array<float> normPositions;
    for (auto value : dbValues)
    {
        float y = juce::jmap(value, rangeMin, rangeMax, top, bottom);
        normPositions.add(y);
    }
    return normPositions;
}


void DBGrid::resized()
{
}


