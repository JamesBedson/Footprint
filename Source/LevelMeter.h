/*
  ==============================================================================

    LevelMeter.h
    Created: 22 May 2023 12:57:10am
    Author:  Iker

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class LevelMeter : public juce::Component
{
public:
	LevelMeter();
	~LevelMeter()			override;
	void paint(juce::Graphics& g) override
	{
		auto bounds = getLocalBounds().toFloat();

		g.setColour(juce::Colours::white.withBrightness(0.4f));
		g.fillRoundedRectangle(bounds, 5.f);
		//map level will go from -60 / 6 to 0/width
		g.setColour(juce::Colours::white);
		const auto scaledX = juce::jmap(level, -60.f, 6.f, 0.f, static_cast<float>(getHeight()));
		g.fillRoundedRectangle(bounds.removeFromBottom(scaledX), 5.f);
	}

	void setLevel(const float value) { level = value; }
private:
	float level = -60.f;
};