#include <Arduino.h>

class NECTransmitter {
public:
  NECTransmitter(uint8_t pin, bool activeLow = true);

  void SendNEC(uint8_t address, uint8_t command) const;

private:
  // Get active value based on the active parameter and the active low / high
  // member.
  uint8_t GetActiveValue(bool active) const;

  void SendByte(uint8_t byte) const;

  void SendPulse(bool value) const;

  // Digital output pin.
  const uint8_t pin;

  // Denotes whether a high or low level indicates active.
  const uint8_t activeValue;
  const uint8_t nonActiveValue;
};
