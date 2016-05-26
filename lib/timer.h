/*
 * @Author: Navarro Torres, Agustin
 *
 * A library to control ARM timer
 *
 * You can find more information in chapter 14 from CM2835 ARM Peripherals
 */

#include "rpi.h"
//0x2000B218
// ARM timer register's address
#define ARM_TIMER_LOAD          (PERIPHERAL_BASE + 0xB400)
#define ARM_TIMER_VALUE         (PERIPHERAL_BASE + 0xB404)
#define ARM_TIMER_CONTROL       (PERIPHERAL_BASE + 0xB408)
#define ARM_TIMER_IRQ_CLEAR     (PERIPHERAL_BASE + 0xB40C)
#define ARM_TIMER_IRQ_RAW       (PERIPHERAL_BASE + 0xB410)
#define ARM_TIMER_IRQ_MASKED    (PERIPHERAL_BASE + 0xB414)
#define ARM_TIMER_RELOAD        (PERIPHERAL_BASE + 0xB418)
#define ARM_TIMER_DIVIDER       (PERIPHERAL_BASE + 0xB41C)
#define ARM_TIMER_COUNTER       (PERIPHERAL_BASE + 0xB420)

// Struct for mapping registers
typedef struct {
    // Sets the timer to count down
    volatile uint32_t load;
    // Current timer value
    volatile uint32_t value;
    /*
     * Control register, bits:
     * 32:16 -> Free running counter pre-scaler
     * 9 -> 0: Free running counter disable / 1: Free running counter entable
     * 8 -> 0: Timers keep running if ARM is in debug halted mode / 1: Timers
     *              halted if ARM is in debug halted mode.
     * 7 -> 0: Timer disable / 1 -> timer enable
     * 5 -> 0: Timer interrupt disable / 1 -> Timer interrup enable
     * 3:2 -> Pre-scale bits: 00 (/1), 01 (/16), 10(/256), 11 (/1)
     * 1 -> 0: 16-bit counters / 1: 23-bit counter
     */
    volatile uint32_t control;
    // Clean the interrupt-pending bit
    volatile uint32_t irq_clear;
    // Status of the interrup pending
    volatile uint32_t irq_raw;
    // Show the interrupt signal
    volatile uint32_t irq_masked;
    // Copy of timer load
    volatile uint32_t reload;
    volatile uint32_t divider;
    volatile uint32_t counter;
} armTimer_t;

// Options control
#define ARM_TIMER_16BIT         (0 << 1)
#define ARM_TIMER_23BIT         (1 << 1)
#define ARM_TIMER_PRESCALE_1    (0 << 2)
#define ARM_TIMER_PRESCALE_16   (1 << 2)
#define ARM_TIMER_PRESCALE_256  (2 << 2)
#define ARM_TIMER_INT_ENABLE    (1 << 5)
#define ARM_TIMER_INT_DISABLE   (0 << 5)
#define ARM_TIMER_ENABLE        (1 << 7)
#define ARM_TIMER_DISABLE       (0 << 7)

// Functions
armTimer_t* getTimer(void);
