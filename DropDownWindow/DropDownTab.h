//
// Created by Mason Self on 8/2/23.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

struct DropDownArrow : public juce::Component
{
    DropDownArrow(juce::Colour _arrowColor, float _lineThickness);
    void paint(juce::Graphics& g) override;

    enum Direction {up, down};
    Direction direction;
    juce::Colour arrowColor;
    float lineThickness;
};

class DropDownTab : public juce::Button
{
public:
    DropDownTab(juce::Colour _backgroundColor, juce::Colour _textColor, juce::String displayText, float arrowThickness);
    void paintButton (juce::Graphics &g, bool, bool) override;
    void resized() override;
    void buttonStateChanged() override;
private:
    DropDownArrow arrow;

    juce::Colour backgroundColor;
    juce::Colour textColor;
    juce::String text;

    bool cachedToggleState{false};
};


