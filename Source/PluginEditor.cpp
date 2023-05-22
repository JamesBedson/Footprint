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
    addAndMakeVisible(levelMeterLeft);
    addAndMakeVisible(levelMeterRight);
    
    addAndMakeVisible(audioProcessor.inputWaveform);
    addAndMakeVisible(audioProcessor.outputWaveform);
    audioProcessor.inputWaveform.setColours(juce::Colours::black.withAlpha(0.7f), juce::Colours::white.withAlpha(0.5f));
    
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
    /*
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::white);
     */
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

    levelMeterLeft.setBounds(350, 50, 15, 210);
    levelMeterRight.setBounds(370, 50, 15, 210);
    
    audioProcessor.inputWaveform.setBounds(390, 50, 300, 50);
    audioProcessor.outputWaveform.setBounds(390, 100, 300, 50);

}

void FootprintAudioProcessorEditor::timerCallback()
{
    levelMeterLeft.setLevel(audioProcessor.getRmsValue(0));
    levelMeterRight.setLevel(audioProcessor.getRmsValue(1));

    levelMeterLeft.repaint();
    levelMeterRight.repaint();
}
