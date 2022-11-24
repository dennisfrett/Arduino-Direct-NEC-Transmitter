#include <Arduino.h>

/// Class that can send unmodulated NEC commands.
class NECTransmitter {
public:
  /// Will set the given digital pin to OUTPUT and pull it to the non-active
  /// value.
  NECTransmitter(uint8_t pin, bool activeLow = true);

  /// Send given NEC command. Only the 8 address bits and the 8 command bits are
  /// needed, the logical inverse is calculated automatically.
  void SendNEC(uint8_t address, uint8_t command) const;

  /// Send given Extended NEC command. 16 address bits and the 8 command bits
  /// are needed, the logical inverse of the command is calculated
  /// automatically.
  void SendExtendedNEC(uint16_t address, uint8_t command) const;

private:
  /// Send the given byte as NEC.
  void SendByte(uint8_t byte, bool includeInverse = true) const;

  /// Send a 0 or 1 pulse. Value `true` means 1, `false` means 0.
  void SendPulse(bool value) const;

  // Digital output pin.
  const uint8_t pin;

  // Denotes whether a high or low level indicates active.
  const uint8_t activeValue;
  const uint8_t nonActiveValue;
};
