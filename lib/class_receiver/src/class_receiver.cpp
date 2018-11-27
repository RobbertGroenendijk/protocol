#include "Arduino.h"
#include "class_receiver.h"

void Receiver::setup(Light* _light) {
  previousMillis = 2000;
  colorSend = false;
  light = _light;
}
void Receiver::reset() {
  currentMillis = millis();
  previousMillis = millis();
  colorSend = false;
  switchState = false;

  Serial.println("RECIEVER reset");
}
void Receiver::initSignal() {
  currentMillis = millis();
  unsigned long elapsedTime = currentMillis - previousMillis;

  if (elapsedTime > 1000 && elapsedTime < 1450) {
    audioProcessor.sendTone(2000);
  } else if (elapsedTime > 1450 && elapsedTime < 1900) {
    audioProcessor.sendTone(3000);
  } else {
    audioProcessor.stopTone();
  }

} // End of Receiver::initSignal();
void Receiver::readySignal() {
  currentMillis = millis();
  unsigned long elapsedTime = currentMillis - previousMillis;

  if (elapsedTime > 2000 && elapsedTime < 2450) {
    audioProcessor.sendTone(600);
  } else if (elapsedTime > 2450 && elapsedTime < 2900) {
    audioProcessor.sendTone(1000);
  } else {
    audioProcessor.stopTone();
  }
}
void Receiver::listenSignal() {
  audioProcessor.saveSignal();
}
void Receiver::confirmSignal(unsigned int _beginTime, unsigned int _endTime) {
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
void Receiver::closeSignal() {
  currentMillis = millis();
  unsigned long elapsedTime = currentMillis - previousMillis;

  if (elapsedTime > 9000 && elapsedTime < 9450) {
    audioProcessor.sendTone(800);
  } else if (elapsedTime > 9450 && elapsedTime < 9900) {
    audioProcessor.sendTone(600);
  } else {
    audioProcessor.stopTone();
  }
}
void Receiver::sendColor(int _colorChannel, int _fftBand) {
  light->saveColor(_colorChannel, _fftBand);
}
void Receiver::increaseLightnumber() {
  light->nextLight();
  Serial.print("current lightNumber:");
  Serial.println(light->lightNumber);
}
void Receiver::run() {
  currentMillis = millis();
  unsigned long elapsedTime = currentMillis - previousMillis;

  //audioProcessor.printFFT();

  if (elapsedTime > 1000 && elapsedTime < 2000) {
    //Serial.println("Receiver");
    initSignal();
    lightNumberIncreased = false;
  } else if (elapsedTime > 2000 && elapsedTime < 3000) {
    readySignal();
  } else if (elapsedTime > 3000 && elapsedTime < 4000) {
    listenSignal();
    colorSend = false;
  } else if (elapsedTime > 4100 && elapsedTime < 4500) {
    // CONFIRMATION
    confirmSignal(4100,4500);
    if (colorSend == false) {
      int fftBand = audioProcessor.getSignal();
      sendColor(0, fftBand);
      colorSend = true;
    }
  } else if (elapsedTime > 5000 && elapsedTime < 6000) {
    listenSignal();
    colorSend = false;
  } else if (elapsedTime > 6100 && elapsedTime < 6500) {
    // CONFIRMATION
    confirmSignal(6100,6500);
    if (colorSend == false) {
      int fftBand = audioProcessor.getSignal();
      sendColor(1, fftBand);
      colorSend = true;
    }
  } else if (elapsedTime > 7000 && elapsedTime < 8000) {
    listenSignal();
    colorSend = false;
  } else if (elapsedTime > 8100 && elapsedTime < 8500) {
    // CONFIRMATION
    confirmSignal(8100,8500);
    if (colorSend == false) {
      int fftBand = audioProcessor.getSignal();
      sendColor(2, fftBand);
      colorSend = true;
    }
  } else if (elapsedTime > 9000 && elapsedTime < 10000) {
    closeSignal();

    if (lightNumberIncreased != true) {
      increaseLightnumber();
      lightNumberIncreased = true;
      audioProcessor.flushFft();
    }
  } else if (elapsedTime > 10000) {
    switchState = true;
  } else {
    audioProcessor.stopTone();
  }
}
