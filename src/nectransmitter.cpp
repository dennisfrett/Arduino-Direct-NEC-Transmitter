#include "nectransmitter.h"

#define NEC_VALUE_PULSE_DURATION 562
#define NEC_0_PAUSE_DURATION 562
#define NEC_1_PAUSE_DURATION 1687

NECTransmitter::NECTransmitter(uint8_t pin, bool activeLow)
    : pin(pin), activeLow(activeLow) {
  pinMode(pin, OUTPUT);

  // Output non-active value.
  digitalWrite(pin, GetActiveValue(false));
}

uint8_t NECTransmitter::GetActiveValue(bool active) const {
  if (active) {
    return activeLow ? LOW : HIGH;
  }

  return activeLow ? HIGH : LOW;
}

void NECTransmitter::SendPulse(bool value) const {
  digitalWrite(pin, GetActiveValue(true));
  delayMicroseconds(NEC_VALUE_PULSE_DURATION);
  digitalWrite(pin, GetActiveValue(false));

  if (value) {
    delayMicroseconds(NEC_1_PAUSE_DURATION);
  } else {
    delayMicroseconds(NEC_0_PAUSE_DURATION);
  }
}

void NECTransmitter::SendByte(uint8_t byte) const {
  // Send normal.
  for (int bit = 0; bit < 8; bit++) {
    SendPulse((byte >> bit) & 1);
  }

  // Send logical inverse.
  for (int bit = 0; bit < 8; bit++) {
    SendPulse(!((byte >> bit) & 1));
  }
}

void NECTransmitter::SendNEC(uint8_t address, uint8_t command) const {
  // Send AGC (9ms pulse)
  digitalWrite(pin, GetActiveValue(true));
  delayMicroseconds(9000);

  // Send space
  digitalWrite(pin, GetActiveValue(false));
  delayMicroseconds(4500);

  // Send address
  SendByte(address);

  // Send code
  SendByte(command);

  // End
  SendPulse(false);
}
