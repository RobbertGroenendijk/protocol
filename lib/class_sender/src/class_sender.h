#ifndef class_sender_h
#define class_sender_h

#include "Arduino.h"
#include "class_audioProcessor.h"
#include "class_light.h"

class Sender {
  public:
    //Sender();
    void setup(Light *_light);
    void reset();
    void initColor();
    void initSignal();
    void sendSignal(int _colorChannel);
    void confirmSignal(unsigned int _beginTime, unsigned int _endTime);
    void closeSignal();
    void increaseLightnumber();
    void run();

    AudioProcessor audioProcessor;
    Light *light;

    bool lightNumberIncreased;

    bool state;
    bool switchState;

    bool sending;
    bool colorInitiated;
    int colorNumber;


    unsigned long previousMillis;
    unsigned long currentMillis;

};

#endif
