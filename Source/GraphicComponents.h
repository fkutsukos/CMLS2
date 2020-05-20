/*
  ==============================================================================

    GraphicComponents.h
    Created: 18 May 2020 1:10:14pm
    Author:  Cillo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class GraphicComponents    : public Component
{
public:
    GraphicComponents();
    ~GraphicComponents();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GraphicComponents)
};
//TEXT COMPONENT
class TextComponent   : public Component
{
public:
    TextComponent();
    ~TextComponent();

    void title(Graphics&);
    void subtitle(Graphics&);
    void resized() override;

    void textnote(Graphics&);
    void textfreq(Graphics&);

private:
   // JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TextComponent)
};