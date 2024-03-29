/*
  ==============================================================================

    ComboBoxLookandFeel.cpp
    Created: 3 Jun 2023 6:43:32pm
    Author:  Iker

  ==============================================================================
*/

#include "ComboBoxLookandFeel.h"

ComboBoxLookandFeel::ComboBoxLookandFeel()
{
}

ComboBoxLookandFeel::~ComboBoxLookandFeel()
{
}

void ComboBoxLookandFeel::paint(juce::Graphics& g)
{
    if (isInside == true)
    {
        auto bounds = getLocalBounds().reduced(6.0f, 6.0f);
        //g.setColour(juce::Colours::white.darker());
        g.setColour(juce::Colours::red);
        g.drawRoundedRectangle(bounds.toFloat(), 10.0f, 1.0f);
    }
}

void ComboBoxLookandFeel::resized()
{
    //juce::Rectangle<int> bounds = getLocalBounds();
    //setBounds(getWidth() / 10 - 70, getHeight() / 2 - 10, 140, 20);
}

void ComboBoxLookandFeel::drawComboBox(juce::Graphics& g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, juce::ComboBox& comboBox)
{
}

juce::Font ComboBoxLookandFeel::getComboBoxFont(juce::ComboBox& comboBox)
{
    juce::Font labelFont;
    labelFont.setTypefaceName("Futura");
    labelFont.setHeight(25.f);

    return labelFont;
}

void ComboBoxLookandFeel::lookAndFeelChanged()
{
}

void ComboBoxLookandFeel::drawMenuBarBackground(juce::Graphics& g, int width, int height, bool isMouseOverBar, juce::MenuBarComponent&)
{
    g.fillAll(juce::Colours::green);
}

void ComboBoxLookandFeel::drawPopupMenuItem(juce::Graphics& g, const juce::Rectangle<int>& area, bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu, const juce::String& text, const juce::String& shortcutKeyText, const juce::Drawable* icon, const juce::Colour* textColourToUse)
{

    juce::Rectangle<int> itemBounds(area.getX(), area.getY(), itemWidth, itemHeight);

    {
        juce::Colour backgroundColour(juce::Colours::white.darker().darker().darker());
        //juce::Colour backgroundColour(juce::Colours::yellow);
        g.setColour(backgroundColour);
        //g.fillRect(itemBounds);

        juce::Font labelFont(getPopupMenuFont());
        labelFont.setTypefaceName("Futura");
        labelFont.setHeight(18.f);
        g.setFont(labelFont);

        if (isHighlighted)
        {
            juce::Colour highlightColour(juce::Colours::white.darker());
            g.setColour(highlightColour);
        }
        else
        {
            juce::Colour itemColour(juce::Colours::white);
            g.setColour(itemColour);
        }

        g.drawFittedText(text, itemBounds.reduced(4, 0), juce::Justification::centredLeft, 1);
    }
}

void ComboBoxLookandFeel::drawPopupMenuBackgroundWithOptions(juce::Graphics& g, int width, int height, const juce::PopupMenu::Options&)
{
    g.fillAll(juce::Colours::white.darker().darker());
}

void ComboBoxLookandFeel::drawPopupMenuBackground(juce::Graphics&, int, int)
{
}

void ComboBoxLookandFeel::mouseEnter(const juce::MouseEvent& event)
{
    isInside = true;
    repaint();
}

void ComboBoxLookandFeel::mouseExit(const juce::MouseEvent& event)
{
    isInside = false;
    repaint();
}
