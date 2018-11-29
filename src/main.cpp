#include <Arduino.h>

#include <class_light.h>
#include <class_receiver.h>
#include <class_sender.h>

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
