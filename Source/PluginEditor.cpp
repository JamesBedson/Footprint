/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FootprintAudioProcessorEditor::FootprintAudioProcessorEditor (FootprintAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    
    
    // "Add and make visible" all child components of the editor
    
    addAndMakeVisible(displaySection);
    addAndMakeVisible(pedalSection);
    addAndMakeVisible(controlSection);
    setSize (1100, 700);
}

FootprintAudioProcessorEditor::~FootprintAudioProcessorEditor()
{
}

//==============================================================================
void FootprintAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::white);

}

void FootprintAudioProcessorEditor::resized()
{
    auto editorBounds       = getBounds();
    auto editorCentre       = editorBounds.getCentre();
    int editorWidth         = getWidth();
    int editorHeight        = getHeight();
    
    int pedalSectionWidth   = 0.85f * editorWidth;
    int pedalSectionHeight  = 0.5f * editorHeight;
    int pedalYOffset        = editorHeight * 0.2f;
    
    pedalSection.setSize(pedalSectionWidth, pedalSectionHeight);
    pedalSection.setCentrePosition(editorCentre.getX(),
                                   editorCentre.getY() + pedalYOffset);
    
    int displaySectionWidth     = 0.6f * editorWidth;
    int displaySectionHeight    = 0.35f * editorHeight;
    auto pedalSectionTopRight   = pedalSection.getBounds().getTopRight();
    
    int displaySectionTopRightY = editorCentre.getY() - editorHeight * 0.45f;
    int displaySectionTopRightX = pedalSectionTopRight.getX();
    
    displaySection.setSize(displaySectionWidth, displaySectionHeight);
    displaySection.setTopRightPosition(displaySectionTopRightX, displaySectionTopRightY);
}
