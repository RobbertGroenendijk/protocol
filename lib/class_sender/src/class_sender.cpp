#include "Arduino.h"
#include "class_sender.h"

void Sender::setup(Light *_light) {
  colorNumber = 0;
  colorInitiated = false;
  previousMillis = 2000;

  light = _light;
}
void Sender::reset() {
  currentMillis = millis();
  previousMillis = millis();
  colorNumber = 0;
  colorInitiated = false;
  lightNumberIncreased = false;
  switchState = false;

  Serial.println("SENDER reset");
}
void Sender::initColor() {
  light->initColor(light->lightNumber);
  colorInitiated = true;
}
void Sender::initSignal() {
  currentMillis = millis();
  unsigned long elapsedTime = currentMillis - previousMillis;

  if (elapsedTime > 1000 && elapsedTime < 1700) {
    audioProcessor.sendTone(1000);
  } else if (elapsedTime > 1700 && elapsedTime < 1900) {
    audioProcessor.sendTone(1500);
  } else {
    audioProcessor.stopTone();
  }
} // End of Sender::initSignal();
void Sender::sendSignal(int _colorChannel) {
  int tempColor = light->pushColorArray[light->lightNumber][_colorChannel];
  int colorFrequency = map(tempColor,0,255,500,5000);

  audioProcessor.sendTone(colorFrequency);
}
void Sender::confirmSignal(unsigned int _beginTime, unsigned int _endTime) {
  currentMillis = millis();
  unsigned long elapsedTime = currentMillis - previousMillis;

  unsigned int timeBlock = (_endTime - _beginTime) / 4;

  if (elapsedTime > _beginTime && elapsedTime < _endTime) {
    if (elapsedTime > _beginTime && elapsedTime < _beginTime + timeBlock) {
      audioProcessor.sendTone(500);
    } else if (elapsedTime > _beginTime + timeBlock && elapsedTime < _beginTime + (timeBlock*2)) {
      audioProcessor.sendTone(900);
    } else if (elapsedTime > _beginTime + (timeBlock*2) && elapsedTime < _beginTime + (timeBlock*3)) {
      audioProcessor.sendTone(800);
    } else if (elapsedTime > _beginTime + (timeBlock*3) && elapsedTime < _beginTime + (timeBlock*4)) {
      audioProcessor.sendTone(700);
    }
  }
}
void Sender::closeSignal() {
  currentMillis = millis();
  unsigned long elapsedTime = currentMillis - previousMillis;

  if (elapsedTime > 9000 && elapsedTime < 9450) {
    audioProcessor.sendTone(600);
  } else if (elapsedTime > 9450 && elapsedTime < 9900) {
    audioProcessor.sendTone(800);
  } else {
    audioProcessor.stopTone();
  }
}
void Sender::increaseLightnumber() {
  light->nextLight();
  Serial.print("current lightNumber:");
  Serial.println(light->lightNumber);
}
void Sender::run() {
  currentMillis = millis();
  unsigned long elapsedTime = currentMillis - previousMillis;

  if (elapsedTime > 1000 && elapsedTime < 2000) {
    //Serial.println("Sender");
    initSignal();
    colorInitiated = false;
    lightNumberIncreased = false;
  } else if (elapsedTime > 2000 && elapsedTime < 3000) {
    if (colorInitiated == false) {
      initColor();
    }
  } else if (elapsedTime > 3000 && elapsedTime < 4000) {
    sendSignal(0);
  } else if (elapsedTime > 4500 && elapsedTime < 4900) {
    // CONFIRMATION
    confirmSignal(4500,4900);
  } else if (elapsedTime > 5000 && elapsedTime < 6000) {
    sendSignal(1);
  } else if (elapsedTime > 6500 && elapsedTime < 6900) {
    // CONFIRMATION
    confirmSignal(6500,6900);
  } else if (elapsedTime > 7000 && elapsedTime < 8000) {
    sendSignal(2);
  } else if (elapsedTime > 8500 && elapsedTime < 8900) {
    // CONFIRMATION
    confirmSignal(8500,8900);
  } else if (elapsedTime > 9000 && elapsedTime < 10000) {
    closeSignal();

    if (lightNumberIncreased != true) {
      increaseLightnumber();
      audioProcessor.flushFft();
      lightNumberIncreased = true;
    }
  } else if (elapsedTime > 10000) {
    switchState = true;
  } else {
    audioProcessor.stopTone();
  }
}
