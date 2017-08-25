/**
 * @Author: Navarro Torres, Agustin
 *
 * A simple controller for rpi b+ gpio
 */

#include "gpio.h"
gpio_t *gpio = (gpio_t *) GPFSEL0;


void setPullUpDownGPIO(unsigned int n, unsigned int value){
    int i;
    //Set pullup
    gpio->gppud = value;
    //System need 150 cycles of set-up control
    for (i = 0;i < 150; ++i) asm(""); //Avoid compiler optimization
    //Modify lines
    if (n <= 32){ 
        gpio->gppudclk0 = (0x01 << (n % 32));
        for (i = 0; i < 150; ++i) asm("");
        gpio->gppudclk0 = 0x0;
    }
    else{
        gpio->gppudclk1 = (0x01 << (n % 32));
        for (i = 0; i < 150; ++i) asm("");
        gpio->gppudclk1 = 0x0;
    }
    return;
}

/**
 *
 * Set GPIO n as pull-up
 */
void setPullUpGPIO(unsigned int n){
    setPullUpDownGPIO(n, 0x02);
    return;
}

/**
 * Set GPIO n as pull-down
 */
void setPullDownGPIO(unsigned int n){
    setPullUpDownGPIO(n, 0x01);
    return;
}

/**
 * Select mode to GPIO n
 */
char setModeGPIO(unsigned int pin, unsigned int mode){
    volatile uint32_t *line;
    line = &(gpio->gpfsel0);

    if (pin > 53) return -1;

    //Select Mode
    switch (mode){
        case INPUT: line[pin / 10] &= GPFSEL_IN(pin); break;
        case OUTPUT: line[pin / 10] |= GPFSEL_OUT(pin); break;
        case INPUT_PULLUP:
            setPullUpGPIO(pin);
            line[pin / 10] &= GPFSEL_IN(pin);
            break;
        case INPUT_PULLDOWN:
            setPullDownGPIO(pin);
            line[pin / 10] &= GPFSEL_IN(pin);
            break;
        case ALT0: line[pin / 10] |= GPFSEL_ALT0(pin); break;
        case ALT1: line[pin / 10] |= GPFSEL_ALT1(pin); break;
        case ALT2: line[pin / 10] |= GPFSEL_ALT2(pin); break;
        case ALT3: line[pin / 10] |= GPFSEL_ALT3(pin); break;
        case ALT4: line[pin / 10] |= GPFSEL_ALT4(pin); break;
        case ALT5: line[pin / 10] |= GPFSEL_ALT5(pin); break;
        default: return -1;
    }
    return 0;
}

/**
 * Write value in GPIOpin
 */

char writeGPIO(unsigned int pin, unsigned int value){
    volatile unsigned int *line;
    if (pin > 53) return -1;

    if (value == HIGH){
        line = &(gpio->gpset0);
        line[pin / 32] = (0x11 << (pin % 32));
    }
    else if (value == LOW){
        line = &(gpio->gpclr0);
        line[pin / 32] = (0x11 << (pin % 32));
    }
    else return -1;
    * line |= (0x11 << (pin % 32));
    return 0;
}

/**
 * Read value from GPIOn
 */
unsigned int readGPIO(unsigned int n){
    volatile unsigned int *line;
    line = &(gpio->gplev0);
    if (n > 53) return -1;
    //Take value
    if (line[n / 32] & (0x01 << (n % 32))) return HIGH;
    else return LOW;
}

/**
 * Change GPIO for using JTAG debugger
 */
void jtag_enable(void){
    setPullUpGPIO(22);
    setModeGPIO(22, ALT4);
    setPullUpGPIO(4);
    setModeGPIO(4, ALT5);
    setPullUpGPIO(27);
    setModeGPIO(27, ALT4);
    setPullUpGPIO(25);
    setModeGPIO(25, ALT4);
    setPullUpGPIO(23);
    setModeGPIO(23, ALT4);
    setPullUpGPIO(24);
    setModeGPIO(24, ALT4);
    return;
}
