# CMLS 
CMLS  Homework 2 , Group 2, Assignment 3 - Guitar Tuner by students:
- 10577360 
- 10650559 
- 10574134 
- 10532582

The requirements for compiling and building the code:
1. Create a new project in JUCE of type 'Audio Plug-In'.
2. Use 'CMLS_Tuner' as project name.
3. Add the dsp module to the list of modules.

The VST audio plugin code consists of 4 .h and 4 .cpp files and an image used as spectrogram background:
-  The PluginProcessor.cpp and .h files that handles the audio input buffer, the midi output messages and the processing logic.
- The PluginEditor.cpp and .h files that handles the onscreen GUI controls and the visualization.
- The FFT.cpp and .h files that computes the FFT for every block of input samples, draws the spectrogram frames and detects the fundamental frequency based on the FFT data.
- The GraphicComponents.cpp and .h files that handles the steady text messages, i.e. title, subtitle and slider label, and the variable ones as the displayed Note estimated and its equivalent Frequency.
- black-wall-surface-background_23-2148067232.jpg

The plugin CMLS_Tuner can be tested using the AudioPluginHost environment of JUCE. 
In order to test the plugin:
- Use the AUAudioFilePlayer sampler to feed a sample guitar wav file as input to the CMLS_Tuner plug-in and in addition connect it to the Audio Output to listen to the sampled guitar wav.
- Connect the midi output of the CMLS_Tuner plugin to AUMIDISynth to synthesize the midi output messages.
- Connect the AUMIDISynth to the Audio output to hear the midi message produced by CMLS_Tuner as audio.

To access the plugin GUI (Figure 3), double click the CMLS_Tuner plugin:
- The GUI displays the note and the frequency correspondent to the estimated pitch and a visualization of the spectrum.
- You can and set the number of harmonics to be used in pitch detection using the relevant slider.
- As an output it produces a noteOn and a noteOff midi message with the detected pitch as a midi note.

