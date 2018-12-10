#ifndef class_audioProcessor_h
#define class_audioProcessor_h

#include "Arduino.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

class AudioProcessor {
  public:
    void setup(AudioControlSGTL5000* _sgtl5000,AudioSynthWaveformSine* _sine, AudioMixer4* _mixer1, AudioMixer4* _mixer2,AudioAnalyzeFFT1024* _fft1024);
    void reset();
    void testTone(char _c);
    void stopTone();
    void toggleMixer(int _mixerNumber, float _volume);
    void sendTone(int _frequency);
    int getHighestFFTBand(int _beginBand, int _endBand);
    void saveSignal();
    int getSignal();
    void flushFft();
    void printFFT();

    AudioControlSGTL5000 *sgtl5000;
    AudioSynthWaveformSine *sine1;
    AudioMixer4 *mixer1;
    AudioMixer4 *mixer2;
    AudioAnalyzeFFT1024 *fft1024_1;

    int arrayIndex;
    int fftBandArray[200];

    unsigned long previousMillis;
    unsigned long currentMillis;

    AudioProcessor();
};

#endif
