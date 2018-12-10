#include <Arduino.h>

#include <class_light.h>
#include <class_receiver.h>
#include <class_sender.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;          //xy=257,311
AudioInputI2S            i2s2;           //xy=338,197
AudioMixer4              mixer2;         //xy=482,313
AudioMixer4              mixer1;         //xy=491,187
AudioAnalyzeFFT1024      fft1024_1;      //xy=653,149
AudioOutputI2S           i2s1;           //xy=662,290
AudioControlSGTL5000     sgtl5000;     //xy=340,58
AudioConnection          patchCord1(sine1, 0, mixer2, 0);
AudioConnection          patchCord2(sine1, 0, mixer2, 1);
AudioConnection          patchCord3(i2s2, 0, mixer1, 0);
AudioConnection          patchCord4(i2s2, 1, mixer1, 1);
AudioConnection          patchCord5(mixer2, 0, i2s1, 0);
AudioConnection          patchCord6(mixer2, 0, i2s1, 1);
AudioConnection          patchCord7(mixer1, fft1024_1);
// GUItool: end automatically generated code

#define BEGIN_STATE 1 // 0 = RECEIVER // 1 = SENDER
#define BUTTON_PIN 0
#define RECIEVER_PIN 1
#define SENDER_PIN 2

Light light;
Sender sender;
Receiver receiver;

void testAudioProcessors();

bool buttonPressed, buttonReleased;

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT);
  pinMode(RECIEVER_PIN, OUTPUT);
  pinMode(SENDER_PIN, OUTPUT);

  light.setup();
  receiver.setup(&light);
  sender.setup(&light);

  receiver.audioProcessor.setup(&sgtl5000,&sine1,&mixer1,&mixer2,&fft1024_1);
  sender.audioProcessor.setup(&sgtl5000,&sine1,&mixer1,&mixer2,&fft1024_1);
  testAudioProcessors();

  buttonPressed = false;
  buttonReleased = true;

  if (BEGIN_STATE == 0) {
    receiver.state = true;
    sender.state = false;

  } else if (BEGIN_STATE == 1) {
    receiver.state = false;
    sender.state = true;
  }

  delay(1000);
}

void loop() {
  delay(10);
  int buttonState;
  buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == HIGH) {
    if (buttonPressed != true) {
      Serial.println("button pressed");

      if (BEGIN_STATE == 0) {
        receiver.state = true;
        sender.state = false;
        receiver.audioProcessor.reset();
        Serial.println("start RECEIVER");
      } else if (BEGIN_STATE == 1) {
        receiver.state = false;
        sender.state = true;
        sender.audioProcessor.reset();
        Serial.println("start SENDER");
      }

      light.reset();
      receiver.reset();
      sender.reset();

      buttonPressed = true;
      buttonReleased = false;
    }
  } else if (buttonState == LOW) {
    if (buttonReleased == false) {
      Serial.println("button released");
      buttonPressed = false;
      buttonReleased = true;
    }
  }

  if (receiver.state == true) {
    receiver.run();
    digitalWrite(SENDER_PIN,LOW);
    digitalWrite(RECIEVER_PIN,HIGH);
  } else if (sender.state == true) {
    sender.run();
    digitalWrite(SENDER_PIN,HIGH);
    digitalWrite(RECIEVER_PIN,LOW);
  }

  if (receiver.switchState == true) {
    receiver.state = false;
    sender.state = true;
    sender.previousMillis = millis();
    receiver.switchState = false;
  } else if (sender.switchState == true) {
    receiver.state = true;
    receiver.previousMillis = millis();
    sender.state = false;
    sender.switchState = false;
  }

  light.run();
}
void testAudioProcessors() {
  receiver.audioProcessor.testTone('r');
  sender.audioProcessor.testTone('s');
}
