#include "Arduino.h"
#include "class_light.h"

void Light::setup() {
  reset();

  for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 3; j++) {
        pinMode(lightPinArray[i][j],OUTPUT);
      }
  }

}
void Light::reset() {
  lightNumber = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      colorArray[i][j] = 0;
      pushColorArray[i][j] = 0;
    }
  }
  Serial.println("LIGHT reset");
}
void Light::setLight(int _lightNumber, int _color[3]) {
    analogWrite(lightPinArray[_lightNumber][0],255);
    analogWrite(lightPinArray[_lightNumber][1],255);
    analogWrite(lightPinArray[_lightNumber][2],255);
}
void Light::run() {

  // forLoop to even out colors and allow fading.
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {

      if (colorArray[i][j] < pushColorArray[i][j]) {
        float colorDifference = pushColorArray[i][j] - colorArray[i][j];
        float colorStep = colorDifference / 50;

        colorArray[i][j] += colorStep;
        setLight(i,colorArray[i]);
      } else if (colorArray[i][j] > pushColorArray[i][j]) {
        float colorDifference = colorArray[i][j] - pushColorArray[i][j];
        float colorStep = colorDifference / 50;

        colorArray[i][j] -= colorStep;
        setLight(i,colorArray[i]);
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
  Serial.print(frequencyRange);
  int frequencyColor = abs(map(frequencyRange,500,5000,0,255));
  Serial.print("current saving color: ");
  Serial.println(frequencyColor);
  pushColorArray[lightNumber][_colorChannel] = frequencyColor;
}
void Light::nextLight() {
  if (lightNumber < 3) {
    lightNumber += 1;
  } else if (lightNumber >= 3) {
    lightNumber = 0;
  }
} // End of Light::nextLight()
