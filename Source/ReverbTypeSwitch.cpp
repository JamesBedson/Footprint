/*
  ==============================================================================

    ReverbTypeSwitch.cpp
    Created: 12 Jun 2023 5:00:36pm
    Author:  Iker

  ==============================================================================
*/

#include "ReverbTypeSwitch.h"

ReverbTypeSwitch::ReverbTypeSwitch(FootprintAudioProcessor* p, const std::string& parameterID)
: choiceAttachment(*p->apvts.getParameter(parameterID), [this](float newValue) {parameterChanged(newValue);})
{
    currentSetting = 3;
    setInterceptsMouseClicks(true, true);
    currentSettingChanged = false;
}

ReverbTypeSwitch::~ReverbTypeSwitch()
{
}

//void ReverbTypeSwitch::paint(juce::Graphics& g)
//{
//    juce::Rectangle<int> bounds = getLocalBounds();
//    int settingWidth = bounds.getWidth() / 4;
//    int settingHeight = bounds.getHeight();
//    int switchHeight = 20;
//
//    // Calculate the position and rectangle for the background rounded rectangle
//    juce::Rectangle<int> backgroundRect(bounds.getX(), (settingHeight - switchHeight) / 2, bounds.getWidth(), switchHeight);
//    g.setColour(juce::Colours::white);
//    g.drawRoundedRectangle(backgroundRect.reduced(5.f, 2.f).toFloat(), 7.f, 1.2f);
//
//    for (int i = 0; i < 4; ++i)
//    {
//        juce::Rectangle<int> settingRect(i * settingWidth, (settingHeight - switchHeight) / 2, settingWidth, switchHeight);
//        if (i == currentSetting)
//        {
//            g.setColour(juce::Colours::white);
//            g.fillRoundedRectangle(settingRect.reduced(6.f, 2.f).toFloat(), 7.f);
//        }
//    }
//}

//void ReverbTypeSwitch::paint(juce::Graphics& g)
//{
//    juce::Rectangle<int> bounds = getLocalBounds();
//    int settingWidth = bounds.getWidth() / 4;
//    int settingHeight = bounds.getHeight();
//    int switchHeight = 15;
//    int ledHeight = 20;
//    float ledInterSpace = 0.88f;
//    float ledSectionDisplacement = 35.f;
//
//    juce::Rectangle<int> buttonRect(bounds.getX(), (settingHeight - switchHeight) / 2, switchHeight, switchHeight);
//    g.setColour(juce::Colours::white);
//    g.fillRoundedRectangle(buttonRect.toFloat(), 5.f);
//
//    int ledSize = ledHeight * 0.5;
//    for (int i = 0; i < 4; ++i)
//    {
//        // Calculate the position and rectangle for each LED
//        juce::Rectangle<int> ledRect((i * settingWidth * ledInterSpace) + ledSectionDisplacement, (settingHeight - ledSize) / 2, ledSize, ledSize);
//
//        // Customize the LED appearance
//        g.setColour(juce::Colours::lightgrey);
//        if (i == currentSetting)
//            g.setColour(juce::Colours::green);
//        g.fillEllipse(ledRect.toFloat());
//    }
//}

void ReverbTypeSwitch::paint(juce::Graphics& g)
{
    //g.fillAll();
    juce::Rectangle<int> bounds = getLocalBounds();
    int settingWidth = bounds.getWidth() / 4;
    int settingHeight = bounds.getHeight();
    int switchHeight = 17;
    int ledHeight = 20;
    float ledInterSpace = 0.78f;
    float ledSectionDisplacement = 35.f;

    juce::Rectangle<int> buttonRect(bounds.getX() + 5, (settingHeight - switchHeight) * 0.25f, switchHeight, switchHeight);
    g.setColour(juce::Colours::white);
    g.fillRoundedRectangle(buttonRect.toFloat(), 5.f);

    for (int i = 0; i < 4; ++i)
    {
        float ledSize = ledHeight * (0.5 + i * 0.1); // Increase the size of the LEDs with each iteration
        int xPos = (i * settingWidth * ledInterSpace) + ledSectionDisplacement;
        int yPos = (settingHeight - ledSize) * 0.5f;
        juce::Rectangle<int> ledRect(xPos, yPos - 22, ledSize, ledSize);

        if (i == currentSetting)
        {
            g.setColour(juce::Colours::mediumseagreen);
            juce::ColourGradient gradient(juce::Colours::mediumseagreen, ledRect.toFloat().getCentre().translated(0, -ledSize * 0.25f),
                juce::Colours::mediumseagreen.darker(), ledRect.toFloat().getCentre().translated(0, ledSize * 0.25f), false);
            g.setGradientFill(gradient);

            g.fillEllipse(ledRect.toFloat());
        }
        else
        {
            g.setColour(juce::Colours::lightgrey);
            g.fillEllipse(ledRect.toFloat());
            g.setColour(juce::Colours::black.withAlpha(0.3f));
            juce::ColourGradient gradient(juce::Colours::black.withAlpha(0.1f), ledRect.toFloat().getCentre().translated(0, -ledSize * 0.25f),
                juce::Colours::black.withAlpha(0.3f), ledRect.toFloat().getCentre().translated(0, ledSize * 0.25f), false);
            g.setGradientFill(gradient);
            g.fillEllipse(ledRect.reduced(2, 2).toFloat());
        }
    }
    juce::Rectangle<int> infoRect(bounds.getX() + 5, bounds.getY() + bounds.getHeight() * 0.7f * 0.85f, bounds.getWidth() * 0.9f, bounds.getHeight() * 0.35);
    juce::Colour baseColor = juce::Colours::lightgrey;
    juce::Colour darkerColor = baseColor.darker(0.4f);
    juce::Colour lighterColor = baseColor.brighter(0.1f);

    g.setColour(darkerColor);
    //g.setGradientFill(juce::ColourGradient(baseColor, infoRect.toFloat().getTopLeft(), darkerColor, infoRect.toFloat().getBottomLeft(), false));
    g.fillRoundedRectangle(infoRect.toFloat(), 5.f);

    juce::Rectangle<float> innerRect = infoRect.reduced(3.f).toFloat();
    //g.setGradientFill(juce::ColourGradient(darkerColor, innerRect.getTopLeft(), lighterColor, innerRect.getBottomLeft(), false));
    g.setColour(baseColor);
    g.fillRoundedRectangle(innerRect, 5.f);

    g.setColour(juce::Colours::white);
    juce::Font reverbFont;
    reverbFont.setTypefaceName("Futura");
    reverbFont.setHeight(GUIAttributes::PedalFontSizes::h3);
    g.setFont(reverbFont);
    

    // Set the text for each case
    switch (currentSetting)
    {
    case 0:
        g.drawText("Bathroom", infoRect, juce::Justification::centred, true);
        break;
    case 1:
        g.drawText("Aranyó Short", infoRect, juce::Justification::centred, true);
        break;
    case 2:
        g.drawText("Aranyó Long", infoRect, juce::Justification::centred, true);
        break;
    case 3:
        g.drawText("Tànger", infoRect, juce::Justification::centred, true);
        break;
    default:
        break;
    }
}


void ReverbTypeSwitch::mouseDown(const juce::MouseEvent& event)
{
    currentSetting = (currentSetting + 1) % 4;
    currentSettingChanged = true;
    repaint();
}

int ReverbTypeSwitch::getCurrentSetting() const
{
    return currentSetting;
}

void ReverbTypeSwitch::parameterChanged(float newValue) {
    
    currentSetting = int(newValue);
    repaint();
}
