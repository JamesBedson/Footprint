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
    const float centreX = (float) x + (float) width * 0.5f;
    const float centreY = (float) y + (float) height * 0.5f;
    const float rx = centreX - radius;
    const float ry = centreY - radius;
    const float rw = radius * 2.0f;
    const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();

    if (radius > 12.0f)
    {
        if (slider.isEnabled())
            g.setColour (slider.findColour (juce::Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));
        else
            g.setColour (juce::Colours::red);

        const float thickness = 0.7f;

        {
            juce::Path filledArc;
            filledArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, angle, thickness);
            g.fillPath (filledArc);
        }

        {
            const float innerRadius = radius * 0.2f;
            juce::Path p;
            p.addTriangle (-innerRadius, 0.0f,
                           0.0f, -radius * thickness * 1.1f,
                           innerRadius, 0.0f);

            p.addEllipse (-innerRadius, -innerRadius, innerRadius * 2.0f, innerRadius * 2.0f);

            g.fillPath (p, juce::AffineTransform::rotation (angle).translated (centreX, centreY));
        }

//        if (slider.isEnabled())
//            g.setColour (slider.findColour (juce::Slider::rotarySliderOutlineColourId));
//        else
//            g.setColour (juce::Colours::red);
//
//        juce::Path outlineArc;
//        outlineArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, thickness);
//        outlineArc.closeSubPath();
//
//        g.strokePath (outlineArc, juce::PathStrokeType (slider.isEnabled() ? (isMouseOver ? 2.0f : 1.2f) : 0.3f));
    }
//    else
//    {
//        if (slider.isEnabled())
//            g.setColour (slider.findColour (juce::Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));
//        else
//            g.setColour (juce::Colours::red);
//
//        juce::Path p;
//        p.addEllipse (-0.4f * rw, -0.4f * rw, rw * 0.8f, rw * 0.8f);
//        juce::PathStrokeType (rw * 0.1f).createStrokedPath (p, p);
//
//        p.addLineSegment (juce::Line<float> (0.0f, 0.0f, 0.0f, -radius), rw * 0.2f);
//
//        g.fillPath (p, juce::AffineTransform::rotation (angle).translated (centreX, centreY));
//    }
}
