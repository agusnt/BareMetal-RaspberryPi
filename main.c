#include "lib/gpio.h"

int main (void){
    unsigned int  wait;
    // Config JTAG
    jtag_enable();

    setModeGPIO(ACT, OUTPUT);
    writeGPIO(ACT, LOW);

    // Blink ACT led
    while(1){
        for(wait = 0; wait < 0x400000; wait++) asm("");
        writeGPIO(ACT, HIGH);
        for(wait = 0; wait < 0x400000; wait++) asm("");
        writeGPIO(ACT, LOW);
    }
    return 0;
}
