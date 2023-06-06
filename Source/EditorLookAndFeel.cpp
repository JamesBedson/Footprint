/*
  ==============================================================================

    EditorLookAndFeel.cpp
    Created: 14 May 2023 10:44:02am
    Author:  James Bedson

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EditorLookAndFeel.h"

//==============================================================================
EditorLookAndFeel::EditorLookAndFeel()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

EditorLookAndFeel::~EditorLookAndFeel()
{
}
void EditorLookAndFeel::drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider)
{
    const float radius = fmin ((float) width * 0.5f, (float) height * 0.5f) - 2.0f;
    const float centerX = (float) x + (float) width * 0.5f;
    const float centerY = (float) y + (float) height * 0.5f;
    const float rx = centerX - radius;
    const float ry = centerY - radius;
    const float rw = radius * 2.0f;
    const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();
    const float outerRadius = radius * 0.9f;

    if (radius > 12.0f)
    {
        if (slider.isEnabled())
            g.setColour (juce::Colours::white.darker().darker());
        else
            g.setColour (juce::Colours::red);
        
        const float thickness = 0.95f;
        
        juce::Path outlineArc;
        outlineArc.addPieSegment(rx + (radius - outerRadius), ry + (radius - outerRadius), rw - (2.0f * (radius - outerRadius)), rw - (2.0f * (radius - outerRadius)), rotaryStartAngle, rotaryEndAngle, thickness + 0.02f);
        //outlineArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, thickness+0.02);
        outlineArc.closeSubPath();
        
        g.strokePath (outlineArc, juce::PathStrokeType (slider.isEnabled() ? (isMouseOver ? 2.0f : 1.2f) : 0.3f));
        
        if (slider.isEnabled())
            g.setColour (juce::Colours::white);
        else
            g.setColour (juce::Colours::red);
        
        //const float thickness = 0.9f;
        
        //Inner part
        {
            juce::Path filledArc;
            filledArc.addPieSegment(rx + (radius - outerRadius), ry + (radius - outerRadius), rw - (2.0f * (radius - outerRadius)), rw - (2.0f * (radius - outerRadius)), rotaryStartAngle, angle, thickness);
            //filledArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, angle, thickness);
            g.fillPath (filledArc);
        }
        
        {
            const float innerRadius = radius * 0.2f;
            juce::Path ellipse1Path;
            
            auto ellipseHeight = innerRadius * 8.0f;
            auto ellipseWidth = innerRadius * 8.0f;
            ellipse1Path.addEllipse(centerX - (ellipseHeight * 0.5f), centerY - (ellipseWidth * 0.5f), ellipseHeight, ellipseWidth);
            g.setColour(juce::Colours::white);
            g.fillPath (ellipse1Path);
            
            juce::Path ellipse2Path;
            
            ellipse2Path.addEllipse(centerX - (ellipseHeight * 0.455f), centerY - (ellipseWidth * 0.455f), innerRadius * 0.7f, innerRadius * 0.7f);
            g.setColour(juce::Colours::black);
            g.fillPath(ellipse2Path, juce::AffineTransform::rotation(angle-90.3f).translated(centerX, centerY));
        }

    }
    /*
    shadowProperties.radius = 40;
    shadowProperties.offset = juce::Point<int>(-1, 4);
    shadowProperties.colour = juce::Colours::white.withAlpha(0.25f);
    dialShadow.setShadowProperties(shadowProperties);
    slider.setComponentEffect(&dialShadow);*/
}

void EditorLookAndFeel::drawToggleButton(juce::Graphics& g, juce::ToggleButton& toggle, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{

    juce::Rectangle<int> bounds = toggle.getLocalBounds().reduced(5.f, 2.f);

    g.setColour(juce::Colours::white);
    g.drawRoundedRectangle(bounds.toFloat(), 7.f, 1.2f);
    //g.setColour(juce::Colours::white);
    if (toggle.getToggleState()) {
        g.fillRoundedRectangle(float(bounds.getX() + float((bounds.getWidth() / 2))), float(bounds.getY()), float(bounds.getWidth() / 2), float(bounds.getHeight()), 7.f);
    }
    else {
        g.fillRoundedRectangle(float(bounds.getX()), float(bounds.getY()), float(bounds.getWidth() / 2), float(bounds.getHeight()), 7.f);
    }
}
