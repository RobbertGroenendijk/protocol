#ifndef class_light_h
#define class_light_h

#include "Arduino.h"

class Light {
  public:
    void setup();
    void run();
    void nextLight();
    void initColor(int _lightNumber);
    void saveColor(int _colorChannel,int _fftBand);

    int lightNumber;


    int colorArray[10][3];
    int pushColorArray[10][3];

    //Light();
};

#endif
