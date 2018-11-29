#include "Arduino.h"
#include "class_light.h"

void Light::setup() {
  lightNumber = 0;
}
void Light::reset() {
  lightNumber = 0;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 3; j++) {
      colorArray[i][j] = 0;
      pushColorArray[i][j] = 0;
    }
  }
  Serial.println("LIGHT reset");
}
void Light::run() {

  // forLoop to even out colors and allow fading.
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 3; j++) {

      if (colorArray[i][j] < pushColorArray[i][j]) {
        colorArray[i][j] += 1;
      } else if (colorArray[i][j] > pushColorArray[i][j]) {
        colorArray[i][j] -= 1;
      }

    } // End of 'j' forLoop
  } // End of 'i' forLoop
} // End of Light::run();
void Light::initColor(int _lightNumber) {
  for (int i = 0; i < 3; i++) {
    pushColorArray[_lightNumber][i] = random(0,255);
    Serial.println(pushColorArray[_lightNumber][i]);
  }
}
void Light::saveColor(int _colorChannel, int _fftBand) {
  int frequencyRange = _fftBand * 43;
  int frequencyColor = map(frequencyRange,500,5000,0,255);
  Serial.print("current saving color: ");
  Serial.println(frequencyColor);
  pushColorArray[lightNumber][_colorChannel] = frequencyColor;
}
void Light::nextLight() {
  if (lightNumber < 9) {
    lightNumber += 1;
  } else if (lightNumber >= 9) {
    lightNumber = 0;
  }
} // End of Light::nextLight()
