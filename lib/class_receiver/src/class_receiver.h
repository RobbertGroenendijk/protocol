#ifndef class_receiver_h
#define class_receiver_h

#include "Arduino.h"
#include "class_audioProcessor.h"
#include "class_light.h"

class Receiver {
  public:
    //Receiver();
    void setup(Light *_light);
    void reset();
    void initSignal();
    void readySignal();
    void listenSignal();
    void confirmSignal(unsigned int _beginTime, unsigned int _endTime);
    void closeSignal();
    void sendColor(int _colorChannel, int _fftBand);
    void increaseLightnumber();
    void run();

    AudioProcessor audioProcessor;
    Light *light;

    bool lightNumberIncreased;

    bool state;
    bool switchState;
    int stepNumber;

    bool colorSend;

    unsigned long previousMillis;
    unsigned long currentMillis;
};

#endif
