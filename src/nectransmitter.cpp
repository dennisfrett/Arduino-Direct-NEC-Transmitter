#include "nectransmitter.h"

#include <util/atomic.h>

#define NEC_VALUE_PULSE_DURATION 562
#define NEC_0_PAUSE_DURATION 562
#define NEC_1_PAUSE_DURATION 1687

NECTransmitter::NECTransmitter(uint8_t pin, bool activeLow)
    : pin(pin), activeValue(activeLow ? LOW : HIGH),
      nonActiveValue(activeLow ? HIGH : LOW) {
  pinMode(pin, OUTPUT);

  // Output non-active value.
  digitalWrite(pin, nonActiveValue);
}

void NECTransmitter::SendPulse(bool value) const {
  digitalWrite(pin, activeValue);
  delayMicroseconds(NEC_VALUE_PULSE_DURATION);
  digitalWrite(pin, nonActiveValue);

  if (value) {
    delayMicroseconds(NEC_1_PAUSE_DURATION);
  } else {
    delayMicroseconds(NEC_0_PAUSE_DURATION);
  }
}

void NECTransmitter::SendByte(uint8_t byte, bool includeInverse) const {
  // Send normal.
  for (int bit = 0; bit < 8; bit++) {
    SendPulse((byte >> bit) & 1);
  }

  if (!includeInverse) {
    return;
  }

  // Send logical inverse.
  for (int bit = 0; bit < 8; bit++) {
    SendPulse(!((byte >> bit) & 1));
  }
}

void NECTransmitter::SendNEC(uint8_t address, uint8_t command) const {

  // Ensure we run atomically.
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { // Send AGC (9ms pulse).
    digitalWrite(pin, activeValue);
    delayMicroseconds(9000);

    // Send space.
    digitalWrite(pin, nonActiveValue);
    delayMicroseconds(4500);

    // Send address.
    SendByte(address);

    // Send code.
    SendByte(command);

    // End.
    SendPulse(false);

    // Reset to non active.
    digitalWrite(pin, nonActiveValue);
  }
}

void NECTransmitter::SendExtendedNEC(uint16_t address, uint8_t command) const {
  // Ensure we run atomically.
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { // Send AGC (9ms pulse).
    digitalWrite(pin, activeValue);
    delayMicroseconds(9000);

    // Send space.
    digitalWrite(pin, nonActiveValue);
    delayMicroseconds(4500);

    // Send address.
    SendByte(address / 256, /* includeInverse */ false);
    SendByte(address & 0xff, /* includeInverse */ false);

    // Send code.
    SendByte(command);

    // End.
    SendPulse(false);

    // Reset to non active.
    digitalWrite(pin, nonActiveValue);
  }
}
