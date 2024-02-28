#include "nectransmitter.h"
#include <Arduino.h>

#define SEND_PIN 8

NECTransmitter necTransmitter(SEND_PIN, /* activeLow */ false);

void setup() {}

void loop() {
  // Will send 0x00FF 0xAB54.
  necTransmitter.SendNEC(0x00, 0xAB);
  delay(1000);
}
