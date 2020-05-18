# CMLS 
CMLS  Homework 2 , Group 2, Assignment 3 - Guitar Tuner:
- 10577360 
- 10650559 
- 10574134 
- 10532582

The VST audio plugin code consists of 3 header and 3 .cpp files: 

- The PluginProcessor.cpp and .h files that handles the audio input buffer, the midi output messages and the processing logic. 

- The PluginEditor.cpp and .h files that handles the onscreen GUI controls and the visualization. 

- The FFT.cpp and .h files that computes the FFT for every block of input samples, draws the spectrogram frames and detects the fundamental frequency based on the FFT data. 

In order to run successfully:
 - Create a new audio plugin project in juce with name "CMLS_Tuner" 
 - add the dsp module to the plugin modules of JUCE.
 - Add midi output interface
