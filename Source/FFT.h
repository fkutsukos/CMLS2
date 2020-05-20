/*
  ==============================================================================

    FFT.h
    Created: 14 May 2020 6:44:05pm
    Author:  Fotis

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class FFT    : public Component , private Timer
{
public:
    FFT(Cmls_tunerAudioProcessor&);
    ~FFT();

    void paint (Graphics&) override;
    void resized() override;
    
    void drawNextFrameOfSpectrum();
    void drawFrame (Graphics& g);
    
    //
    std::vector<int> newMidiNotes;
    int harmonics;
    float fundFreq = 0.0f;
    std::string noteToPrint;
    float freqToPrint;
    
private:
    enum
    {
        scopeSize = 512
    };
    
    float m_scopeData [scopeSize];
    Cmls_tunerAudioProcessor& processor;
    dsp::FFT m_forwardFFT;
    dsp::WindowingFunction<float> m_window;
    
    //the timer callback function is calling the drawNextFrameOfSpectrum()
    //only when the next FFT block is ready AND
    //resets the nextFFTBlockReady flag and updates the GUI using the repaint() function
    void timerCallback() override;
    void pitchDetection();
    float midiToFreq(int& note);
    std::string freqToNote(float& freq);
    const std::string noteName[12] =  {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FFT)
};
