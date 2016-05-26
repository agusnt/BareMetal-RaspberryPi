/**
 * @author: Navarro Torres, Agustín
 *
 * A simple GPIO interface for Raspberry Pi 1 b+
 **/
#include "rpi.h"

#define HIGH (unsigned int)1
#define LOW (unsigned int)0

#ifdef RPiBplus
    #define ACT 47
    #define PWR 35
#else 
    #define ACT 16
#endif


//GPIO Mode
#define INPUT   0x00
#define OUTPUT  0x01
#define ALT0    0x04
#define ALT1    0x05
#define ALT2    0x06
#define ALT3    0x07
#define ALT4    0x03
#define ALT5    0x02
#define INPUT_PULLUP    0x08
#define INPUT_PULLDOWN  0x09

//GPIO Address
//More info see page 90 from
//https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2835/BCM2835-ARM-Peripherals.pdf
#define GPIO_BASE   (PERIPHERAL_BASE + 0x200000)
//GPIO function select
#define GPFSEL0     (GPIO_BASE + 0x00)
#define GPFSEL1     (GPIO_BASE + 0x04)
#define GPFSEL2     (GPIO_BASE + 0x08)
#define GPFSEL3     (GPIO_BASE + 0x0c)
#define GPFSEL4     (GPIO_BASE + 0x10)
#define GPFSEL5     (GPIO_BASE + 0x14)
//GPIO Pin output set
#define GPSET0      (GPIO_BASE + 0x1c)
#define GPSET1      (GPIO_BASE + 0x20)
//GPIO Pin output clear
#define GPCLR0      (GPIO_BASE + 0x28)
#define GPCLR1      (GPIO_BASE + 0x2c)
//GPIO Pin level 0
#define GPLEV0      (GPIO_BASE + 0x34)
#define GPLEV1      (GPIO_BASE + 0x38)
//GPIO pin event detect status
#define GPEDS0      (GPIO_BASE + 0x40)
#define GPEDS1      (GPIO_BASE + 0x44)
//GPIO pin rising edge detect enable
#define GPREN0      (GPIO_BASE + 0x4c)
#define GPREN1      (GPIO_BASE + 0x50)
//GPIO pin falling edge detect enable
#define GPFEN0      (GPIO_BASE + 0x58)
#define GPFEN1      (GPIO_BASE + 0x5c)
//GPIO pin high detect enable
#define GPHEN0      (GPIO_BASE + 0x64)
#define GPHEN1      (GPIO_BASE + 0x68)
//GPIO pin low detect enable 0
#define GPLEN0      (GPIO_BASE + 0x70)
#define GPLEN1      (GPIO_BASE + 0x74)
//GPIO pin async rising edge detect
#define GPAREN0     (GPIO_BASE + 0x7c)
#define GPAREN1     (GPIO_BASE + 0x80)
//GPIO pin async Falling edge detect
#define GPAFEN0     (GPIO_BASE + 0x88)
#define GPAFEN1     (GPIO_BASE + 0x8c)
//GPIO pin pull-up/down enable
#define GPPUD       (GPIO_BASE + 0x94)
#define GPPUDCLK0   (GPIO_BASE + 0x98)
#define GPPUDCLK1   (GPIO_BASE + 0x9c)

//Struct to manipulate GPIO
typedef struct{
    volatile uint32_t gpfsel0;
    volatile uint32_t gpfsel1;
    volatile uint32_t gpfsel2;
    volatile uint32_t gpfsel3;
    volatile uint32_t gpfsel4;
    volatile uint32_t gpfsel5;
    //No used value, next adress + 0x8, not + 0x4
    volatile uint32_t dummy_0;
    volatile uint32_t gpset0;
    volatile uint32_t gpset1;
    //No used value, next adress + 0x8, not + 0x4
    volatile uint32_t dummy_1;
    volatile uint32_t gpclr0;
    volatile uint32_t gpclr1;
    //no used value, next adress + 0x8, not + 0x4
    volatile uint32_t dummy_2;
    volatile uint32_t gplev0;
    volatile uint32_t gplev1;
    //no used value, next adress + 0x8, not + 0x4
    volatile uint32_t dummy_3;
    volatile uint32_t gpeds0;
    volatile uint32_t gpeds1;
    //no used value, next adress + 0x8, not + 0x4
    volatile uint32_t dummy_4;
    volatile uint32_t gpren0;
    volatile uint32_t gpren1;
    //no used value, next adress + 0x8, not + 0x4
    volatile uint32_t dummy_5;
    volatile uint32_t gpfen0;
    volatile uint32_t gpfen1;
    //no used value, next adress + 0x8, not + 0x4
    volatile uint32_t dummy_6;
    volatile uint32_t gphen0;
    volatile uint32_t gphen1;
    //no used value, next adress + 0x8, not + 0x4
    volatile uint32_t dummy_7;
    volatile uint32_t gplen0;
    volatile uint32_t gplen1;
    //no used value, next adress + 0x8, not + 0x4
    volatile uint32_t dummy_8;
    volatile uint32_t gparen0;
    volatile uint32_t gparen1;
    //no used value, next adress + 0x8, not + 0x4
    volatile uint32_t dummy_9;
    volatile uint32_t gpafen0;
    volatile uint32_t gpafen1;
    //no used value, next adress + 0x8, not + 0x4
    volatile uint32_t dummy_10;
    volatile uint32_t gppud;
    volatile uint32_t gppudclk0;
    volatile uint32_t gppudclk1;
} gpio_t;
//Mask select for GPFSELF
//with AND
#define GPFSEL_IN(n) (~(0x07 << ((n % 10) * 3)))
//with OR
#define GPFSEL_OUT(n)  (OUTPUT << ((n % 10) * 3))
#define GPFSEL_ALT0(n) (ALT0 << ((n % 10) * 3))
#define GPFSEL_ALT1(n) (ALT1 << ((n % 10) * 3))
#define GPFSEL_ALT2(n) (ALT2 << ((n % 10) * 3))
#define GPFSEL_ALT3(n) (ALT3 << ((n % 10) * 3))
#define GPFSEL_ALT4(n) (ALT4 << ((n % 10) * 3))
#define GPFSEL_ALT5(n) (ALT5 << ((n % 10) * 3))

//Functions
void setPullUpGPIO (unsigned int n);
void setPullDownGPIO (unsigned int n);
char setModeGPIO (unsigned int pin, unsigned int mode);
char writeGPIO (unsigned int pin, unsigned int value);
unsigned int readGPIO (unsigned int n);
void jtag_enable();
