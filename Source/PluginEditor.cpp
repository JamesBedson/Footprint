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
    addAndMakeVisible(levelInMeterLeft);
    addAndMakeVisible(levelInMeterRight);
    addAndMakeVisible(levelOutMeterLeft);
    addAndMakeVisible(levelOutMeterRight);
    setSize (1100, 700);
    startTimerHz(24);
}

FootprintAudioProcessorEditor::~FootprintAudioProcessorEditor()
{
}

//==============================================================================
void FootprintAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.drawImage(background, getLocalBounds().toFloat(), juce::RectanglePlacement::stretchToFit);
    g.setColour(juce::Colours::white);
    //juce::Line<float> line1(juce::Point<float>((getLocalBounds().getWidth() * 0.25f) - 17.0f, getLocalBounds().getHeight() * 0.5f), juce::Point<float>((getLocalBounds().getWidth() * 0.25f) + 20.0f, getLocalBounds().getHeight() * 0.5f));
    //juce::Line<float> line2(juce::Point<float>((getLocalBounds().getWidth() * 0.5f) - 17.0f, getLocalBounds().getHeight() * 0.5f), juce::Point<float>((getLocalBounds().getWidth() * 0.5f) + 20.0f, getLocalBounds().getHeight() * 0.5f));
    //juce::Line<float> line3(juce::Point<float>((getLocalBounds().getWidth() * 0.75f) - 17.0f, getLocalBounds().getHeight() * 0.5f), juce::Point<float>((getLocalBounds().getWidth() * 0.75f) + 20.0f, getLocalBounds().getHeight() * 0.5f));
    //juce::Line<float> line4(juce::Point<float>((getLocalBounds().getWidth()) - 17.0f, getLocalBounds().getHeight() * 0.5f), juce::Point<float>((getLocalBounds().getWidth()) + 50.0f, getLocalBounds().getHeight() * 0.5f));
    //g.drawLine(line1, 2.0f);
    //g.drawLine(line2, 2.0f);
    //g.drawLine(line3, 2.0f);
    //g.drawLine(line4, 2.0f);
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
    
    int displaySectionWidth     = 0.62f * editorWidth;
    int displaySectionHeight    = 0.35f * editorHeight;
    auto pedalSectionTopRight   = pedalSection.getBounds().getTopRight();
    
    int displaySectionTopRightY = editorCentre.getY() - editorHeight * 0.45f;
    int displaySectionTopRightX = pedalSectionTopRight.getX();
    
    displaySection.setSize(displaySectionWidth, displaySectionHeight);
    displaySection.setTopRightPosition(displaySectionTopRightX, displaySectionTopRightY);

    int controlSectionWidth = 0.2f * editorWidth;
    int controlSectionHeight = displaySectionHeight;
    auto controlSectionTopLeft = pedalSection.getBounds().getTopLeft();

    int controlSectionTopLeftY = displaySectionTopRightY;
    int controlSectionTopLeftX = pedalSectionTopRight.getX() - pedalSectionWidth;

    controlSection.setSize(controlSectionWidth, controlSectionHeight);
    controlSection.setTopLeftPosition(controlSectionTopLeftX, controlSectionTopLeftY);

    levelInMeterLeft.setBounds(350, 50, 15, 210);
    levelInMeterRight.setBounds(370, 50, 15, 210);

    levelOutMeterLeft.setBounds(420, 50, 15, 210);
    levelOutMeterRight.setBounds(440, 50, 15, 210);

}

void FootprintAudioProcessorEditor::timerCallback()
{
    levelInMeterLeft.setLevel(audioProcessor.getInRmsValue(0));
    levelInMeterRight.setLevel(audioProcessor.getInRmsValue(1));

    levelOutMeterLeft.setLevel(audioProcessor.getOutRmsValue(0));
    levelOutMeterRight.setLevel(audioProcessor.getOutRmsValue(1));

    levelInMeterLeft.repaint();
    levelInMeterRight.repaint();
    levelOutMeterLeft.repaint();
    levelOutMeterRight.repaint();
}