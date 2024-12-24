# Arduino Direct NEC Transmitter

## Why is this useful?

This library can be used to control devices with an 3.5mm "IR input" directly using an Arduino microcontroller, without the need for an IR LED.

## Which devices are compatible?

- Devices that support [removable IR receivers / extenders](https://www.google.com/search?q=3.5mm+ir+extender&source=lnms&tbm=isch)
- Amplifiers with an "IR input" port, used to chain devices

As long as they work with (Extended) NEC, this library should work. I've tested the library with a NAD amplifier and a TOSLINK optical switcher.
More information on the NEC IR protocol: https://techdocs.altium.com/display/FPGA/NEC+Infrared+Transmission+Protocol

## How is this different from regular IR?

An IR remote typically sends out pulses that are modulated at 38khz.
These pulses are received by an IR receiver (like the TSOP devices). 
An IR receiver is an IR photodiode and circuitry that filters out the 38khz carrier wave. The output of this receiver is the unmodulated IR signal that was received by the remote. 

The receiving device expects an unmodulated signal on the data line.

This library cannot be used to control an IR LED directly, since there modulation is required.
There are multiple libraries out there that can be used to control IR LEDs from Arduino:
- https://github.com/Arduino-IRremote/Arduino-IRremote
- https://github.com/ukw100/IRMP

## Connections

Sometimes, the IR input port will provide power on one of the pins. When connecting your controller to such an input, it's probably best if you only connect the data line (*ring*) and ground (*sleeve*), the current requirement of the microcontroller is likely too high for the device to provide.

### IR extenders

Some IR controllable devices come with a removable IR receiver, typically connected to a 3.5mm/2.5mm male headphone jack. These often do not have a separate power supply, and are powered through the cable.

The pinout of these devices is typically as follows:
- **Tip**: Provides 5V for the IR receiver.
- **Ring**: Data. Activates on a pulse. Typically active low.
- **Sleeve**: Ground.

### Amplifier IR input

Conceptually almost the same as the IR extenders, but these typically do not supply power and use mono 3.5mm/2.5mm male headphone jack cables.

The pinout of these devices is typically as follows:
- **Tip**: Data. Activates on a pulse. Typically active low.
- **Sleeve**: Ground.
