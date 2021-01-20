# Arduino Direct NEC Transmitter
An IR remote typically sends out pulses that are modulated at 38khz.
These pulses are received by an IR receiver (like the TSOP devices). 
An IR receiver is basically an IR photodiode and circuitry that filters out the 38khz carrier wave. The output of this receiver is the unmodulated IR signal that was received by the remote. 

Some IR controllable devices come with a removable IR receiver, typically connected to a 3.5mm/2.5mm male headphone jack. 
The pinout of these devices is typically as follows:
- **Tip**: Provides 5V for the IR receiver.
- **Ring**: Activates on a pulse. Typically active low.
- **Sleeve**: Ground.

The ring expected an unmodulated signal. 

This libary allows you to connect any microcontroller, like an Arduino or even a Raspberry Pi directly to the IR input of such a device, completely bypassing the need for emitting the signal through an IR LED.

When connecting your controller to such an input, it's probably best if you only connect the data line (*ring*) and ground (*sleeve*), the current requirement of the microcontroller is likely too high for the device to provide.

See for more information on the NEC IR protocol: https://techdocs.altium.com/display/FPGA/NEC+Infrared+Transmission+Protocol
