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
    numOfHarmonics.addListener(this);
    startTimerHz (60);
    numOfHarmonics.setSliderStyle(Slider::LinearHorizontal);
    getLookAndFeel().setColour(Slider::thumbColourId, Colours::white);
    getLookAndFeel().setColour(Slider::trackColourId, Colours::darkorange);
    getLookAndFeel().setColour(Slider::backgroundColourId, Colours::darkgrey);
    numOfHarmonics.setRange(1.0,8.0,1);
    numOfHarmonics.setPopupMenuEnabled(true);
    numOfHarmonics.setValue(0.0);
    numOfHarmonics.setTextBoxStyle(Slider::TextBoxLeft, false, 20, numOfHarmonics.getTextBoxHeight());
    addAndMakeVisible(numOfHarmonics);

    numOfHarmonicsLabel.setText("Number of Harmonics", dontSendNotification);
    numOfHarmonicsLabel.setFont(Font("Courier New",16.0f,Font::plain));
    numOfHarmonicsLabel.attachToComponent(&numOfHarmonics, false);
    //numOfHarmonicsLabel.setColour();
    addAndMakeVisible(numOfHarmonicsLabel);
    setSize (500, 420);
    addAndMakeVisible(texts);
    addAndMakeVisible(noteLabel);
    addAndMakeVisible(freqLabel);
}


Cmls_tunerAudioProcessorEditor::~Cmls_tunerAudioProcessorEditor()
{

}


void Cmls_tunerAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    fft.harmonics = numOfHarmonics.getValue();
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

void Cmls_tunerAudioProcessorEditor::paint(Graphics& g)
{
    Image background = ImageCache::getFromMemory(BinaryData::blackwallsurfacebackground_232148067232_jpg, BinaryData::blackwallsurfacebackground_232148067232_jpgSize);
    //g.drawImageAt(background, 0, 0);

    texts.title(g);
    texts.subtitle(g);
   
    g.setOpacity (1.0f);
    //g.setColour (Colours::white);
    fft.paint(g);

    Rectangle<int> area = getLocalBounds();
    Rectangle<int> areaDown = area.removeFromBottom(120);
    ColourGradient myGradient(Colours::transparentBlack, 0, (5 / 8) * 420 , Colours::darkslategrey, 500, 420, false);
    g.setGradientFill(myGradient);
    //g.setColour(Colours::darkslategrey);
    g.fillRect(areaDown);

    

    Rectangle<int> outF(390, 310, 100, 100);
    ColourGradient myGradient1(Colours::brown, outF.getX(), outF.getY(), Colours::orange, outF.getX(), outF.getY() + outF.getHeight(),false);
    g.setGradientFill(myGradient1);
    g.fillRoundedRectangle(outF.getX(), outF.getY(), outF.getWidth(), outF.getHeight(),5);

    Rectangle<int> outN(280, 310, 100, 100);
    ColourGradient myGradient2(Colours::brown, outN.getX(), outN.getY(), Colours::orange, outN.getX(), outN.getY() + outN.getHeight(), false);
    g.setGradientFill(myGradient1);   
    g.fillRoundedRectangle(outN.getX(), outN.getY(), outN.getWidth(), outN.getHeight(), 5);

    texts.textnote(g);
    texts.textfreq(g);

    noteLabel.setText(fft.noteToPrint, dontSendNotification);
    freqLabel.setText(std::to_string(fft.freqToPrint) + " Hz", dontSendNotification);
    Font aFont("Agency FB", "regular", 20.0f);
    noteLabel.setFont(aFont);
    noteLabel.setColour(Label::textColourId, Colours::black);
    noteLabel.setJustificationType(Justification::centred);
    freqLabel.setFont(aFont);
    freqLabel.setColour(Label::textColourId, Colours::black);
    freqLabel.setJustificationType(Justification::centred);
}


void Cmls_tunerAudioProcessorEditor::resized()
{
    Rectangle<int> area = getLocalBounds();
    Rectangle<int> areaTop = area.removeFromTop(300);
    //Rectangle<int> areaDown = area.removeFromBottom(120);
  
    fft.setBounds(areaTop);
    //numOfHarmonics.setBoundsRelative(0.1f, 0.775f, 0.25f, 0.25f);
    numOfHarmonics.setBounds(10, 350, 240, 50);

    noteLabel.setBounds(280, 310, 100, 100);
    freqLabel.setBounds(390, 310, 100, 100);

}




