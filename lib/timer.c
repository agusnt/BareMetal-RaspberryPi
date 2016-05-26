/**
 * Author: Navarro Torres, Agustin
 *
 * A controller for ARM Timer
 *
 * Chapter 14 BCM2835 ARM Peripherals
 */

#include "timer.h"
armTimer_t *timer = (armTimer_t *) ARM_TIMER_LOAD;

armTimer_t* getTimer (void){
    return timer;
}
