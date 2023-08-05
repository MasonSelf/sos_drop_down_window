//
// Created by Mason Self on 8/2/23.
//

#include "DropDownTab.h"

DropDownArrow::DropDownArrow(juce::Colour _arrowColor, float _lineThickness)
: arrowColor(_arrowColor), lineThickness(_lineThickness)
{
    setInterceptsMouseClicks(false, false);
}

void DropDownArrow::paint(juce::Graphics& g)
{
    auto xThird = static_cast<float>(getWidth()) / 3.0f;
    auto yThird = static_cast<float>(getHeight()) / 3.0f;
    g.setColour(arrowColor);

    //assume direction is down
    juce::Point<float> leftEnd {xThird, yThird};
    juce::Point<float> midPoint { static_cast<float>(getWidth()) / 2.0f, yThird * 2.0f};
    juce::Point<float> rightEnd {xThird * 2.0f, yThird};

    //flip if direction is up
    if (direction == Direction::up)
    {
        leftEnd.y += yThird;
        midPoint.y -= yThird;
        rightEnd.y += yThird;
    }

    //draw arrow
    g.drawLine({leftEnd, midPoint}, lineThickness);
    g.drawLine({rightEnd, midPoint}, lineThickness);
    auto halfLineWidth = lineThickness / 2.0f;
    g.fillEllipse(midPoint.x - halfLineWidth, midPoint.y - halfLineWidth, lineThickness, lineThickness);
}

DropDownTab::DropDownTab(juce::Colour _backgroundColor, juce::Colour _textColor, juce::String displayText, float arrowThickness)
: juce::Button(displayText), arrow(_textColor, arrowThickness), backgroundColor(_backgroundColor), textColor(_textColor), text(displayText)
{
    setToggleable(true);
    setClickingTogglesState(true);
    addAndMakeVisible(arrow);
}
void DropDownTab::paintButton (juce::Graphics &g, bool, bool)
{
    g.setColour(backgroundColor);
    g.setOpacity(0.5f);
    g.fillAll();

    g.setColour(textColor);
    g.setFont(12.0f);
    g.drawFittedText(text, 3, 0, getWidth(), getHeight(), juce::Justification::centredLeft, 1);
}
void DropDownTab::resized()
{
    arrow.setBounds(getWidth() - getHeight(), 0, getHeight(), getHeight());
}

void DropDownTab::buttonStateChanged()
{
    if (getToggleState() != cachedToggleState)
    {
        cachedToggleState = getToggleState();
        if (cachedToggleState == true)
        {
            arrow.direction = DropDownArrow::Direction::down;
            arrow.repaint();
        }
        else
        {
            arrow.direction = DropDownArrow::Direction::up;
            arrow.repaint();
        }
    }
}