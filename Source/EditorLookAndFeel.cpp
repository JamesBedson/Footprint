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
    
    if (radius > 12.0f)
    {
        if (slider.isEnabled())
            g.setColour (juce::Colours::white.darker().darker());
        else
            g.setColour (juce::Colours::red);
        
        const float thickness = 0.95f;
        
        juce::Path outlineArc;
        outlineArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, thickness+0.02);
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
            filledArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, angle, thickness);
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
            
            ellipse2Path.addEllipse(centerX - (ellipseHeight * 0.5f), centerY - (ellipseWidth * 0.5f), innerRadius * 0.8f, innerRadius * 0.8f);
            g.setColour(juce::Colours::black);
            g.fillPath(ellipse2Path, juce::AffineTransform::rotation(angle-90.2f).translated(centerX, centerY));
        }
        
        //Outer part
        /*if (slider.isEnabled())
            g.setColour (juce::Colours::white.darker());
        else
            g.setColour (juce::Colours::red);
        
        juce::Path outlineArc;
        outlineArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, thickness);
        outlineArc.closeSubPath();
        
        g.strokePath (outlineArc, juce::PathStrokeType (slider.isEnabled() ? (isMouseOver ? 2.0f : 1.2f) : 0.3f));*/
    }
}

