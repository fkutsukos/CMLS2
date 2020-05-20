/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Cmls_tunerAudioProcessor::Cmls_tunerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::mono(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{

}

Cmls_tunerAudioProcessor::~Cmls_tunerAudioProcessor()
{
}

//==============================================================================
const String Cmls_tunerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Cmls_tunerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Cmls_tunerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Cmls_tunerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Cmls_tunerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Cmls_tunerAudioProcessor::getNumPrograms()
{
    return 1;
}

int Cmls_tunerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Cmls_tunerAudioProcessor::setCurrentProgram (int index)
{
}

const String Cmls_tunerAudioProcessor::getProgramName (int index)
{
    return {};
}

void Cmls_tunerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Cmls_tunerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
    nextFFTBlockReady = false;
    
    for (int i = 0; i < fftSize*2 ; i++){
        fftData[i]=0.0f;
    }
    
    for (int i = 0; i < fftSize ; i++){
        m_fifo[i]=0.0f;
    }
    
    newMidiNote = 0;
    
}

void Cmls_tunerAudioProcessor::releaseResources()
{
    
    for (int i = 0; i < fftSize*2 ; i++){
        fftData[i]=0.0f;
    }
    
    for (int i = 0; i < fftSize ; i++){
        m_fifo[i]=0.0f;
    }
    
    newMidiNote = 0;
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Cmls_tunerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Cmls_tunerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{

    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    if (buffer.getNumChannels() > 0)
    {
        auto* channelData = buffer.getReadPointer (0, 0);
 
        for (auto i = 0; i < buffer.getNumSamples(); ++i)
            
            pushNextSampleIntoFifo (channelData[i]);
    }
    

    // we create a buffer because the existing buffer is empty
    MidiBuffer midiBuffer;
    MidiMessage m1;
    MidiMessage m2;
    if (newMidiNote > 0 && newMidiNote < 128 && soundIsOver == true )
    {
        m1 = MidiMessage::noteOn (1, newMidiNote, (uint8) 100);
        midiBuffer.addEvent(m1,0);
        
        m2 = MidiMessage::noteOn(1, newMidiNote, (uint8) 0);
        midiBuffer.addEvent(m2,50000);
        
        newMidiNote = 0;
    }
    midiMessages.swapWith(midiBuffer);
}


//==============================================================================
bool Cmls_tunerAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* Cmls_tunerAudioProcessor::createEditor()
{
    return new Cmls_tunerAudioProcessorEditor (*this);
}

//==============================================================================
void Cmls_tunerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
}

void Cmls_tunerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}


void Cmls_tunerAudioProcessor::pushNextSampleIntoFifo (float sample) noexcept
{
    if (m_fifoIndex == fftSize)    // [11]
    {
        if (! nextFFTBlockReady) // [12]
        {
            zeromem (fftData, sizeof (fftData));
            memcpy (fftData, m_fifo, sizeof (m_fifo));
            nextFFTBlockReady = true;
        }
 
        m_fifoIndex = 0;
    }
 
    m_fifo[m_fifoIndex++] = sample;  // [12]
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Cmls_tunerAudioProcessor();
}

