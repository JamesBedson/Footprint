/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FootprintAudioProcessorEditor::FootprintAudioProcessorEditor (FootprintAudioProcessor& p)
: AudioProcessorEditor (&p), audioProcessor (p), displaySection(p), pedalSection(&p), controlSection(&p)
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
    g.drawImage(background, getLocalBounds().toFloat(), juce::RectanglePlacement::stretchToFit);
    g.setColour(juce::Colours::white);
    juce::Font font;
    font.setHeight(GUIAttributes::ControlFontSizes::h1);
    font.setTypefaceName("Futura");
    g.setFont(font);
    juce::Rectangle<int> textBounds (getLocalBounds().getX() + 40, getLocalBounds().getY() + 5, getLocalBounds().getWidth() * 0.25f, getLocalBounds().getHeight() * 0.15f);
    g.drawText("FOOTPRINT", textBounds,
        juce::Justification::centred, true);

    paintDecor(g);
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

}

void FootprintAudioProcessorEditor::paintDecor(juce::Graphics& g) {

    juce::Line<float> line1(juce::Point<float>((getLocalBounds().getWidth() * 0.125f), getLocalBounds().getHeight() * 0.45f), juce::Point<float>((getLocalBounds().getWidth() * 0.97f), getLocalBounds().getHeight() * 0.45f));
    juce::Line<float> line2(juce::Point<float>((getLocalBounds().getWidth() * 0.92f), getLocalBounds().getHeight() * 0.7f), juce::Point<float>((getLocalBounds().getWidth() * 0.97f), getLocalBounds().getHeight() * 0.7f));
    juce::Line<float> line3(juce::Point<float>((getLocalBounds().getWidth() * 0.03f), getLocalBounds().getHeight() * 0.7f), juce::Point<float>((getLocalBounds().getWidth() * 0.08f), getLocalBounds().getHeight() * 0.7f));
    juce::Line<float> line4(juce::Point<float>((getLocalBounds().getWidth() * 0.97f), getLocalBounds().getHeight() * 0.45f), juce::Point<float>((getLocalBounds().getWidth() * 0.97f), getLocalBounds().getHeight() * 0.7f));
    juce::Line<float> line5(juce::Point<float>((getLocalBounds().getWidth() * 0.03), getLocalBounds().getHeight() * 0.20755f), juce::Point<float>((getLocalBounds().getWidth() * 0.076f), getLocalBounds().getHeight() * 0.20755f));
    juce::Line<float> line6(juce::Point<float>((getLocalBounds().getWidth() * 0.03), getLocalBounds().getHeight() * 0.20755f), juce::Point<float>((getLocalBounds().getWidth() * 0.03f), getLocalBounds().getHeight() * 0.7f));
    juce::Line<float> line7(juce::Point<float>((getLocalBounds().getWidth() * 0.125f), getLocalBounds().getHeight() * 0.45f), juce::Point<float>((getLocalBounds().getWidth() * 0.125f), getLocalBounds().getHeight() * 0.38f));

    g.drawLine(line1, 2.0f);
    g.drawLine(line2, 2.0f);
    g.drawLine(line3, 2.0f);
    g.drawLine(line4, 2.0f);
    g.drawLine(line5, 2.0f);
    g.drawLine(line6, 2.0f);
    g.drawLine(line7, 2.0f);

}
