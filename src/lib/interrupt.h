/**
 * @Author: Navarro Torres, Agustin
 *
 * Basic information for rpi interrupts
 *
 * More information chapter 7 from BCM2835 ARM Peripherals
 */
#include "rpi.h"

// Memory adress of interruption
#define INTERRUPT_BASE      (PERIPHERAL_BASE + 0xB000)
#define IRQ_BASIC_PENDING   (INTERRUPT_BASE + 0x200)
#define IRQ_PENDING_1       (INTERRUPT_BASE + 0x204)
#define IRQ_PENDING_2       (INTERRUPT_BASE + 0x208)
#define FIQ_CONTROL         (INTERRUPT_BASE + 0x20C)
#define ENABLE_IRQ_1        (INTERRUPT_BASE + 0x210)
#define ENABLE_IRQ_2        (INTERRUPT_BASE + 0x214)
#define ENABLE_BASIC_IRQ    (INTERRUPT_BASE + 0x218)
#define DISABLE_IRQ_1       (INTERRUPT_BASE + 0x21C)
#define DISABLE_IRQ_2       (INTERRUPT_BASE + 0x220)
#define DISABLE_BASIC_IRQ   (INTERRUPT_BASE + 0x224)

// Struct for mapping in memory interrup register
typedef struct{
    volatile uint32_t IRQ_base_pending;
    volatile uint32_t IRQ_pending_1;
    volatile uint32_t IRQ_pending_2;
    volatile uint32_t FIQ_control;
    volatile uint32_t enable_IRQ_1;
    volatile uint32_t enable_IRQ_2;
    volatile uint32_t enable_basic_IRQ;
    volatile uint32_t disable_IRQ_1;
    volatile uint32_t disable_IRQ_2;
    volatile uint32_t diable_basic_IRQ;
} interrupt_t;

// IRQ types
#define IRQ_ARM_TIMER           (1 << 0)
#define IRQ_ARM_MAILBOX         (1 << 1)
#define IRQ_ARM_DOORBELL_0      (1 << 2)
#define IRQ_ARM_DOORBELL_1      (1 << 3)
#define IRQ_GPU0_HALTED         (1 << 4)
#define IRQ_GPU1_HALTED         (1 << 5)
#define IRQ_ARM_ACCESS_ERROR_1  (1 << 6)
#define IRQ_ARM_ACCESS_ERROR_0  (1 << 7)

// Functions
interrupt_t* getInterrupt(void);
