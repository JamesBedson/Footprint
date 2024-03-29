/*
  ==============================================================================

    PedalLookAndFeel.cpp
    Created: 14 May 2023 10:43:50am
    Author:  James Bedson

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PedalLookAndFeel.h"

//==============================================================================
PedalLookAndFeel::PedalLookAndFeel()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

PedalLookAndFeel::~PedalLookAndFeel()
{
}

void PedalLookAndFeel::drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider)
{
    const float radius = fmin ((float) width * 0.5f, (float) height * 0.5f) - 2.0f;
    const float centerX = (float) x + (float) width * 0.5f;
    const float centerY = (float) y + (float) height * 0.5f;
    const float rx = centerX - radius;
    const float ry = centerY - radius;
    const float rw = radius * 2.0f;
    //const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    const float sliderRange = rotaryEndAngle - rotaryStartAngle;
    const float angle = rotaryStartAngle + (sliderPos * sliderRange);
    const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();
    const float outerRadius = radius * 0.83f;

    if (radius > 12.0f)
    {
        if (slider.isEnabled())
            //g.setColour (slider.findColour (juce::Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));
            g.setColour(juce::Colours::white.darker().darker().darker());
        else
            g.setColour (juce::Colours::red);

        const float thickness = 0.9f;

        juce::Path outlineArc;
        outlineArc.addPieSegment(rx + (radius - outerRadius), ry + (radius - outerRadius), rw - (2.0f * (radius - outerRadius)), rw - (2.0f * (radius - outerRadius)), rotaryStartAngle, rotaryEndAngle, thickness + 0.07f);
        //outlineArc.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, thickness + 0.07f);
        outlineArc.closeSubPath();
        g.strokePath(outlineArc, juce::PathStrokeType(slider.isEnabled() ? (isMouseOver ? 2.0f : 1.2f) : 0.3f));

        //Outer part
        if (slider.isEnabled())
            //g.setColour (slider.findColour (juce::Slider::rotarySliderOutlineColourId));
            g.setColour(juce::Colours::white);
            //g.fillAll(juce::Colours::white);
        else
            g.setColour(juce::Colours::black);

        //Inner part
        {
            juce::Path filledArc;
            filledArc.addPieSegment(rx + (radius - outerRadius), ry + (radius - outerRadius), rw - (2.0f * (radius - outerRadius)), rw - (2.0f * (radius - outerRadius)), rotaryStartAngle, angle, thickness);
            //filledArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, angle, thickness);
            g.fillPath (filledArc);
        }

        {
            const float innerRadius = radius * 0.2f;


            juce::Path ellipsePath;
            auto ellipseHeight = innerRadius * 7.0f;
            auto ellipseWidth = innerRadius * 7.0f;
            ellipsePath.addEllipse(centerX - (ellipseHeight * 0.5f), centerY - (ellipseWidth * 0.5f), ellipseHeight, ellipseWidth);
            g.setColour(juce::Colours::white);
            g.fillPath(ellipsePath);

            juce::Path linePath;
            linePath.startNewSubPath(centerX, centerY);
            juce::Line<float> line (juce::Point<float>(5,5), juce::Point<float>(13, 13));
            g.setColour(juce::Colours::black);
            linePath.addLineSegment(line, 2);
            g.fillPath(linePath, juce::AffineTransform::rotation(angle - 90.3f).translated(centerX, centerY));
            g.setColour(juce::Colours::white);
            
        }
        
    }
    /*
    shadowProperties.radius = 24;
    shadowProperties.offset = juce::Point<int>(-1, 4);
    shadowProperties.colour = juce::Colours::black.withAlpha(0.25f);
    dialShadow.setShadowProperties(shadowProperties);
    slider.setComponentEffect(&dialShadow);*/
}

void PedalLookAndFeel::drawToggleButton(juce::Graphics& g, juce::ToggleButton& byPassSwitch, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    g.setColour(juce::Colours::transparentBlack);
    g.drawEllipse(byPassSwitch.getLocalBounds().toFloat(), 10.0f);
    g.setColour(juce::Colours::white);
    g.fillEllipse(byPassSwitch.getLocalBounds().toFloat());
}
