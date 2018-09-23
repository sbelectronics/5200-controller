# Scott's Atari 5200 Controller
smbaker@smbaker.com 
http://www.smbaker.com/

## Purpose

This is a custom controller for the Atari 5200 vintage gaming console. The 5200's original controller do not self center, which is consider by many to be a considerable drawback to the controllers. The fire buttons are also mushy, and the controller is generally unreliable unless rebuilt.

So I made my own.

## Programming the microcontroller

The microcontroller is an ATTINY85.

### Programming with minipro on a TL866

This is the workflow I used when programming from windows, using a TL866 programmer. The TL866 is the style programmer where you remove the chip from the pcboard and insert it into the programmer. Make sure to program both fuses.hex to the fuses, and 5200controller.hex to the program memory.

### Programming ICSP with usbasp/avrdude from ubuntu

This is the workflow I used to do in-circuit serial programming from Ubuntu, using a usbasp programmer. The advantage of this workflow is that no ICs need to be removed from the pcboard. Only revision 0.9 and above of the pcboard have the ICSP header. You may also be able to use a windows version of avrdude instead of using ubuntu. I have not tried windows. The following two commands will program the uses and the flash:

    make fuses
    make flash


## Acknowledgements

Ben Heck has a similar project, in his video "Atari 5200: Making a Better Controller" that demonstrated the technique of using a microcontroller and digital pot to do the potentiometer scaling.
