/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
//#include <chrono>
#include <ctime>
#include <math.h>

//==============================================================================
Cmls_tunerAudioProcessorEditor::Cmls_tunerAudioProcessorEditor (Cmls_tunerAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p), fft(p)
{

    startTimerHz (60);
    numOfHarmonics.setSliderStyle(Slider::IncDecButtons);
    numOfHarmonics.setRange(1.0,6.0,1);
    numOfHarmonics.setPopupMenuEnabled(true);
    numOfHarmonics.setTextValueSuffix("Number of Harmonics");
    numOfHarmonics.setValue(0.0);
    addAndMakeVisible(&numOfHarmonics);
    setSize (700, 500);
}


Cmls_tunerAudioProcessorEditor::~Cmls_tunerAudioProcessorEditor()
{

}

void Cmls_tunerAudioProcessorEditor::timerCallback()
{
    repaint();
    
    // checking if the sound is over so to calculate the most frequently
    // appeared midi note during the sound
    if (processor.soundIsOver == true && fft.newMidiNotes.size() > 0 )
    {
        // find the most frequent midi note in the vector
        processor.newMidiNote =  FindMode(fft.newMidiNotes);
    
        // emptying the vector
        fft.newMidiNotes.clear();
        std::cout << "emptying vector....size now: " << fft.newMidiNotes.size() << std::endl;
        std::cout << "new pitch detected!____ " << processor.newMidiNote << std::endl;
    }
    
}

int Cmls_tunerAudioProcessorEditor::FindMode(std::vector<int>& midiNotes)
{
    int index = 0;
    int highest = 0;
    for (unsigned int a = 0; a < midiNotes.size(); a++)
    {
        int count = 1;
        int Position = midiNotes.at(a);
        for (unsigned int b = a + 1; b < midiNotes.size(); b++)
        {
            if (midiNotes.at(b) == Position)
            {
                count++;
            }
        }
        if (count >= index)
        {
            index = count;
            highest = Position;
        }
    }
    return highest;
}

void Cmls_tunerAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::black);
    g.setOpacity (1.0f);
    g.setColour (Colours::white);
    fft.paint(g);
}

void Cmls_tunerAudioProcessorEditor::resized()
{

    Rectangle<int> area = getLocalBounds();
    Rectangle<int> areaTop = area.removeFromTop(getHeight() / 2);
    Rectangle<int> areaDown = area.removeFromBottom(getHeight() / 2);
    
    fft.setBounds(areaTop);
    numOfHarmonics.setBounds(areaDown);
}




