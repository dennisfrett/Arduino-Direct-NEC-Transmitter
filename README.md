# Arduino Direct NEC Transmitter
An IR remote typically sends out pulses that are modulated at 38khz.
These pulses are received by an IR receiver (like the TSOP devices). 
An IR receiver is basically an IR photodiode and circuitry that filters out the 38khz carrier wave. The output of this receiver is the unmodulated IR signal that was received by the remote. 

In general, there are two situations where this can be used:
- Devices that support [removable IR receivers / extenders](https://www.google.com/search?q=3.5mm+ir+extender&source=lnms&tbm=isch)
- Amplifiers with an IR input

As long as they work with (Extended) NEC, this library should work. I've tested the library with a NAD amplifier and a TOSLINK optical switcher.

See for more information on the NEC IR protocol: https://techdocs.altium.com/display/FPGA/NEC+Infrared+Transmission+Protocol

The receiving device expects an unmodulated signal on the data line.

This libary allows you to connect any microcontroller, like an Arduino or even a Raspberry Pi directly to the IR input of such a device, completely bypassing the need for emitting the signal through an IR LED.

When connecting your controller to such an input, it's probably best if you only connect the data line (*ring*) and ground (*sleeve*), the current requirement of the microcontroller is likely too high for the device to provide.

This library cannot be used to control an IR LED directly, since there modulation is required.
There are multiple libraries out there that can be used to control IR LEDs from Arduino:
- https://github.com/Arduino-IRremote/Arduino-IRremote
- https://github.com/ukw100/IRMP

## Pinouts

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
