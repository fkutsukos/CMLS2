/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "FFT.h"

//==============================================================================
/**
*/
class Cmls_tunerAudioProcessorEditor  : public AudioProcessorEditor , private Timer
{
public:
    Cmls_tunerAudioProcessorEditor (Cmls_tunerAudioProcessor&);
    ~Cmls_tunerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void timerCallback() override;
    
    void drawNextFrameOfSpectrum();
    
        enum
    {
        scopeSize = 512
    };
    int FindMode(std::vector<int>& midiNotes);
    
    
private:
    Cmls_tunerAudioProcessor& processor;
    FFT fft;
    
    
    //Slider for harmonics
    Slider numOfHarmonics;
    Label numOfHarmonicsLabel;
    
   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Cmls_tunerAudioProcessorEditor)
};
