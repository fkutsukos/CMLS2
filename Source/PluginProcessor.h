/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class Cmls_tunerAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    Cmls_tunerAudioProcessor();
    ~Cmls_tunerAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;


    enum
        {
            fftOrder  = 11,
            fftSize   = 1 << fftOrder
            
        };
    

    float fftData [2 * fftSize];
    bool nextFFTBlockReady = false;
    int  sampleRate = getSampleRate();
    
    int newMidiNote = 0;
    bool soundIsOver=true;
    
private:
    // FFT Variables
    float m_fifo [fftSize];                
    int m_fifoIndex = 0 ;
    void pushNextSampleIntoFifo (float sample) noexcept;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Cmls_tunerAudioProcessor)
};
