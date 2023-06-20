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

//void DBGrid::paint(juce::Graphics& g)
//{
//    juce::Rectangle<int> bounds = getLocalBounds();
//    int numDivisions = 10; // Adjust the number of dB divisions as desired
//    int divisionHeight = bounds.getHeight() / numDivisions;
//
//    // Set up the font and color for drawing the dB values
//    juce::Font font(GUIAttributes::DisplayFontSizes::h4);
//    juce::Colour fontColor(juce::Colours::white);
//
//    g.setFont(font);
//    g.setColour(fontColor);
//
//    // Draw the dB values grid
//    for (int i = 0; i <= numDivisions; ++i)
//    {
//        int yPos = bounds.getY() + i * divisionHeight;
//
//        // Draw the horizontal line
//        g.setColour(juce::Colours::lightgrey);
//        g.drawLine(bounds.getX(), yPos, bounds.getRight(), yPos, 1.0f);
//
//        // Draw the dB value
//        int dbValue = i * (-10); // Adjust the dB value calculation as desired
//        juce::String dBText = juce::String(dbValue) + " dB";
//        juce::Rectangle<int> textBounds(bounds.getX(), yPos, bounds.getWidth(), divisionHeight);
//        g.drawFittedText(dBText, textBounds, juce::Justification::centred, 1);
//    }
//}

//void DBGrid::paint(juce::Graphics& g)
//{
//    juce::Rectangle<int> bounds = getLocalBounds();
//    int numDivisions = 19; // Adjust the number of dB divisions as desired
//    double dBRange = 60.0; // Adjust the range of dB values as desired
//    double divisionHeight = static_cast<double>(bounds.getHeight()) / numDivisions;
//
//    // Set up the font and color for drawing the dB values
//    juce::Font font(GUIAttributes::DisplayFontSizes::h4);
//    juce::Colour fontColor(juce::Colours::white);
//
//    g.setFont(font);
//    g.setColour(fontColor);
//
//    // Draw the dB values grid
//    for (int i = 0; i <= numDivisions; ++i)
//    {
//        double yPos = bounds.getY() + i * divisionHeight;
//
//        // Draw the horizontal line
//        g.setColour(juce::Colours::lightgrey);
//        g.drawLine(bounds.getX(), static_cast<int>(yPos), bounds.getRight() - 20.f, static_cast<int>(yPos), 1.0f);
//
//        // Calculate the dB value
//        double normalizedPosition = static_cast<double>(i) / numDivisions;
//        double dbValue = std::pow(10.0, normalizedPosition * dBRange / 20.0);
//        dbValue = 20.0 * std::log10(dbValue);
//
//        // Draw the dB value
//        juce::String dBText = juce::String(static_cast<int>(dbValue)) + " dB";
//        juce::Rectangle<int> textBounds(bounds.getX(), static_cast<int>(yPos), bounds.getWidth(), static_cast<int>(divisionHeight));
//        g.drawFittedText(dBText, textBounds, juce::Justification::centred, 1);
//    }
//}

//labelBounds.setBounds(bounds.getX(), y, bounds.getX() + 30, y + 20);
//g.setColour(juce::Colours::white.darker());
//juce::Font labelFont;
//labelFont.setTypefaceName("Futura");
//labelFont.setHeight(GUIAttributes::DisplayFontSizes::h4);
//g.setFont(labelFont);
//g.drawFittedText(label, labelBounds, juce::Justification::centredRight, 1);
void DBGrid::paint(juce::Graphics& g)
{
    //g.setColour(juce::Colours::red);
    //g.fillAll();
    juce::Rectangle<int> bounds = getLocalBounds();
    float top = bounds.getY();
    float bottom = bounds.getBottom();
    juce::Array<float> normPositions;
    g.setColour(juce::Colours::white.darker().darker().darker().darker());

    for (auto value : dbValues)
    {
        float y = juce::jmap(value, GUIAttributes::LevelMeterRange::minLMR, GUIAttributes::LevelMeterRange::maxLMR, top, bottom);
        normPositions.add(y);
        juce::Line<float> line{float(bounds.getX()), y, float(bounds.getRight()), y };
        g.drawLine(line);
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

        float fontSize = juce::jmap(std::abs(value), GUIAttributes::LevelMeterRange::maxLMR, GUIAttributes::LevelMeterRange::minLMR, float(GUIAttributes::DisplayFontSizes::h7), float(GUIAttributes::DisplayFontSizes::h8));
        font.setHeight(fontSize);
        g.setFont(font);
        g.drawText(label, (bounds.getWidth() / 2) * 0.45f, positionsRev[i], 30, 10, juce::Justification::centred);
        i += 1;
    }
}

juce::Array<float> DBGrid::getPositions()
{
    juce::Rectangle<int> bounds = getLocalBounds();
    float top = bounds.getY();
    float bottom = bounds.getBottom();
    juce::Array<float> normPositions;
    for (auto value : dbValues)
    {
        float y = juce::jmap(value, GUIAttributes::LevelMeterRange::minLMR, GUIAttributes::LevelMeterRange::maxLMR, top, bottom);
        normPositions.add(y);
    }
    return normPositions;
}


void DBGrid::resized()
{
}


