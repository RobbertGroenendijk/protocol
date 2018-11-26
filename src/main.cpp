#include <Arduino.h>

#include <class_light.h>
#include <class_receiver.h>
#include <class_sender.h>

#define BEGIN_STATE 1 // 0 = RECEIVER // 1 = SENDER

Light light;
Sender sender;
Receiver receiver;

void testAudioProcessors();

void setup() {
  Serial.begin(9600);

  light.setup();
  receiver.setup(&light);
  sender.setup(&light);

  testAudioProcessors();

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
  if (receiver.state == true) {
    receiver.run();
  } else if (sender.state == true) {
    sender.run();
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
