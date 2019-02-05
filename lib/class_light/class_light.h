#ifndef class_light_h
#define class_light_h

#include "Arduino.h"
#include "Adafruit_TLC59711.h"

class Light {
  public:
    void setup();
    void reset();
    void run();
    void nextLight();
    void setLight(int _lightNumber, int _color[3]);
    void initColor(int _lightNumber);
    void saveColor(int _colorChannel,int _fftBand);

    int lightNumber;

    Adafruit_TLC59711 *tlc;

    int colorArray[4][3];
    int pushColorArray[4][3];
    int lightPinArray[4][3] = {
      { // Light 1 pins RGB
        2,3,4
      },
      { // Light 2 pins RGB
        5,8,29
      },
      { // Light 3 pins RGB
        30,35,36
      },
      { // Light 4 pins RGB
        37,38,20
      }
    };

    //Light();
};

#endif
