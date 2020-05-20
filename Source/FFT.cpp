/*
  ==============================================================================

    FFT.cpp
    Created: 14 May 2020 6:44:05pm
    Author:  Fotis

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FFT.h"
#include <string>

//==============================================================================
FFT::FFT(Cmls_tunerAudioProcessor& p) : processor (p) , m_forwardFFT(processor.fftOrder), m_window(processor.fftSize, dsp::WindowingFunction<float>::hann) 
{
    setOpaque (true);
    startTimerHz (60);


}

FFT::~FFT()
{
}

void FFT::timerCallback()
{
    if (processor.nextFFTBlockReady)
    {
        drawNextFrameOfSpectrum();
        processor.nextFFTBlockReady = false;
        repaint();
    }
}

void FFT::paint (Graphics& g)
{
    g.setOpacity (1.0f);
    ColourGradient myGradient(Colours::brown, 0, (5 / 8) * 420-50, Colours::orange, 0, (5 / 8)* 420, false);
    g.setGradientFill(myGradient);
    //g.setColour (Colours::orange);
    drawFrame (g);
}

void FFT::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void FFT::drawNextFrameOfSpectrum()
{
    m_window.multiplyWithWindowingTable(processor.fftData,processor.fftSize);
    m_forwardFFT.performFrequencyOnlyForwardTransform(processor.fftData);
    
    pitchDetection();
    
    auto mindB = -100.0f;
    auto maxdB =    0.0f;
 
    for (int i = 0; i < scopeSize; ++i)
    {
        auto skewedProportionX = 1.0f - std::exp (std::log (1.0f - i / (float) scopeSize) * 0.2f);
        auto fftDataIndex = jlimit (0, processor.fftSize / 2, (int) (skewedProportionX * processor.fftSize / 2));
        auto level = jmap (jlimit (mindB, maxdB, Decibels::gainToDecibels (processor.fftData[fftDataIndex])
                                   - Decibels::gainToDecibels ((float) processor.fftSize)),
                           mindB, maxdB, 0.0f, 1.0f);
        
        m_scopeData[i] = level;
    }

}

void FFT::drawFrame (Graphics& g)
{
    
    for (int i = 1; i < scopeSize; ++i)
    {
        auto width  = getLocalBounds().getWidth();
        auto height = getLocalBounds().getHeight();
 
        g.drawLine ({ (float) jmap (i - 1, 0, scopeSize - 1, 0, width),
                              jmap (m_scopeData[i - 1], 0.0f, 1.0f, (float) height, 0.0f),
                      (float) jmap (i,     0, scopeSize - 1, 0, width),
                              jmap (m_scopeData[i],     0.0f, 1.0f, (float) height, 0.0f) });
    }
}

float FFT::midiToFreq(int& note)
{
  return (pow(2, ((note-69)/12.0)))*440;

}

std::string FFT::freqToNote(float& freq)
{
    float A4 = 440;
    float C0 = A4*pow(2, -4.75);
    float h = round(12*log2(freq/C0));
    int octave = h / 12;
    int n = int(h)%12;
    std::string octave_str = std::to_string(octave);
    return noteName[n] + octave_str;
}

void FFT::pitchDetection()
{
    
    float maxBin = 0.0f;
    int midiNote = 0;
    //processor.newMidiNote = 0;
    
    
    static const int frequencies = processor.fftSize/2;
    //std::cout << "frequencies: " << frequencies << std::endl;
    //std::cout << "processor.fftSize * 2: " << processor.fftSize*2 << std::endl;
    
    float frequenciesArray [frequencies];
    zeromem (frequenciesArray, sizeof (frequenciesArray));
    memcpy (frequenciesArray, processor.fftData, sizeof(processor.fftData)/4);
    
    
    
    float HarmonicSum[frequencies];
    zeromem(HarmonicSum, sizeof(HarmonicSum));
    
    for (int index = 0; index < frequencies; index++) {
        for (int i = 0; i <= harmonics; i++) {
            if ((index * i) > frequencies) {
                break;
            }
            else {
                HarmonicSum[index]+= frequenciesArray[index * i];
            }
        }
    }
    maxBin = std::distance(HarmonicSum, std::max_element(HarmonicSum, HarmonicSum + frequencies));

    
    if (HarmonicSum[(int)maxBin] > 1 )
    {
        //There is incoming sound
        processor.soundIsOver = false;
        
        if (newMidiNotes.size()>0)
        {
           std::cout << "Vector had " << newMidiNotes.size() << " elements" << fundFreq << std::endl;
        }
        else
        {
            std::cout << "Vector had no data " << newMidiNotes.size() << " elements" << fundFreq << std::endl;
        }
            
        
        fundFreq = (processor.getSampleRate()/2) * (maxBin/frequencies);
        midiNote = roundToInt(log(fundFreq/440.0)/log(2) * 12 + 69);
        midiNote = midiNote > 0 && midiNote < 129 ? midiNote : 0;
        
        // add the detected pitch as  MIDI note into the vector
        newMidiNotes.push_back(midiNote);
        
        noteToPrint = freqToNote(fundFreq);
        freqToPrint = fundFreq;

        std::cout << "maxBin[" << maxBin << "]: " << fundFreq << std::endl;
        std::cout << "midiNote : " << midiNote << std::endl;
        std::cout << "Note : " << freqToNote(fundFreq) << std::endl;
       
        fundFreq = 0.0f;
    }
    
    if (HarmonicSum[(int)maxBin] < 1 && newMidiNotes.size()>0)
    {
        // We have received a zero so we are considering the sound is over
        std::cout << "we have received a zero so we are considering the sound is over " <<  maxBin <<  std::endl;
        processor.soundIsOver = true;
        
        //processor.newMidiNote = 0;
        //std::cout << "maxBin == 0  processor.soundIsOver to  true: " <<  processor.soundIsOver << std::endl;
    }
        
    //std::cout << " End of pitchdetection() , soundIsOver: " <<  processor.soundIsOver  << std::endl ;
    
}

