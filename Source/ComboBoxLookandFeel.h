/*
  ==============================================================================

    ComboBoxLookandFeel.h
    Created: 3 Jun 2023 6:43:32pm
    Author:  Iker

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ComboBoxLookandFeel : public juce::LookAndFeel_V4, public juce::Component
{
public:
    ComboBoxLookandFeel();
    ~ComboBoxLookandFeel() override;

    void paint(juce::Graphics&)                        override;
    void resized()                                      override;

    void drawComboBox(juce::Graphics& g, int width, int height, bool isButtonDown,
                int buttonX, int buttonY, int buttonW, int buttonH, juce::ComboBox& comboBox) override;
    juce::Font getComboBoxFont(juce::ComboBox& comboBox) override;

    void lookAndFeelChanged() override;

    void drawPopupMenuItem(juce::Graphics& g, const juce::Rectangle<int>& area,
        bool isSeparator, bool isActive, bool isHighlighted,
        bool isTicked, bool hasSubMenu, const juce::String& text,
        const juce::String& shortcutKeyText,
        const juce::Drawable* icon, const juce::Colour* textColourToUse) override;

    void mouseEnter(const juce::MouseEvent& event)      override;
    void mouseExit(const juce::MouseEvent& event)       override;

protected:
    bool isInside = true;
    float comboWidth;
    float comboHeight;
    int itemWidth = 150;
    int itemHeight = 30;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ComboBoxLookandFeel)
};
