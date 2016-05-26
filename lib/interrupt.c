/**
 * Author: Navarro Torres, Agustin
 */

#include "gpio.h"
#include "timer.h"
#include "interrupt.h"
#include "rpi.h"


//Memory mapped interrupt register set
interrupt_t* interrupt = (interrupt_t *) IRQ_BASIC_PENDING;

interrupt_t* getInterrupt (void){
    return interrupt;
}

/*
 * Reset Vector, probably never call
 */
void __attribute__((interrupt("ABORT"))) reset_vector(void){}

/**
 * CPU jump here if an undefined instruccion is found.
 *
 * For debugging
 */
void __attribute__((interrupt("UNDEF"))) undefined(void){
    while(1);
}

/**
 * Interrupt handler
 */
void __attribute__((interrupt("SWI"))) sw_interrupt(void){
        while(1);
}

/**
 * Prefetch abort
 */
void __attribute__((interrupt("ABORT"))) prefetch_abort(void){}

/**
 * Data abort
 */
void __attribute__((interrupt("ABORT"))) data_abort(void){}

/**
 * IRQ handler
 */
void __attribute__((interrupt("IRQ"))) irq(void){
    static char on = 0;
    getTimer()->irq_clear = 1;
    if (on){
        writeGPIO(ACT, HIGH);
        on = 0;
    }
    else{
        writeGPIO(ACT, LOW);
        on = 1;
    }
}

/*
 * FIQ handler
 */
void __attribute__((interrupt("FIQ"))) fiq(void){}
