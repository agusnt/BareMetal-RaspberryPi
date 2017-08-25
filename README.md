# BareMetal RPi

A simple code to run RaspberryPi without a Operating System, and enable JTAG for
debugging or import your own code in a easy way.

The below code is influenced by: [dwelch67](https://github.com/dwelch67/raspberrypi)

## Instalation

Just compile it with ``` make ``` inside src folder, and copy the **kernel.img** onto an SD.

In the SD should be the following files: start.elf, bootcode.bin, fixup.dat and
config.txt. You can download them from the [official repository](https://github.com/raspberrypi/firmware/tree/master/boot)

### Extra

For mor information visit [Valvers](http://www.valvers.com/open-software/raspberry-pi/step01-bare-metal-programming-in-cpt1/)
