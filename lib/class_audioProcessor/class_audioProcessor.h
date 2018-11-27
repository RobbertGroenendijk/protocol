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
    void setup();
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

    int arrayIndex;
    int fftBandArray[200];

    unsigned long previousMillis;
    unsigned long currentMillis;

    AudioProcessor();
};

#endif
