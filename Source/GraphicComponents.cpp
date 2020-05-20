/*
  ==============================================================================

    GraphicComponents.cpp
    Created: 18 May 2020 1:10:14pm
    Author:  Cillo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GraphicComponents.h"

//==============================================================================
GraphicComponents::GraphicComponents()
{
    
}

GraphicComponents::~GraphicComponents()
{
}

void GraphicComponents::paint(Graphics& g)
{

}
void GraphicComponents::resized()
{
    
}

//TEXT COMPONENT
TextComponent::TextComponent()
{
    
}

TextComponent::~TextComponent()
{
}

void TextComponent::title(Graphics& g)
{
    Font myFont("Courier New", "regular", 25.0f);
    g.setFont(myFont);
    g.setColour(Colours::whitesmoke);
    g.drawText("Guitar Tuner", 0, 5, 495, 100, Justification::topRight );

}

void TextComponent::subtitle(Graphics& g)
{
    Font myFont("Courier New", "regular", 15.0f);
    g.setFont(myFont);
    g.setColour(Colours::whitesmoke);
    g.drawText("CMLS - Group 2", 0, 30, 495, 50, Justification::topRight);

}

void TextComponent::textnote(Graphics& g)
{
    Font myFont("Courier New", "regular", 15.0f);
    myFont.setBold(true);
    g.setFont(myFont);
    g.setColour(Colours::whitesmoke);
    g.drawText("Note", 280, 310, 100, 10, Justification::centredTop);
}

void TextComponent::textfreq(Graphics& g)
{
    Font myFont("Courier New", "regular", 15.0f);
    myFont.setBold(true);
    g.setFont(myFont);
    g.setColour(Colours::whitesmoke);
    g.drawText("Frequency", 390, 310, 100, 10, Justification::centredTop);
}

void TextComponent::resized()
{
    
}