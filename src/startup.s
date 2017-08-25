
.global _start


.section ".text"
_start:
    /*
     * Interrupt Vector
     */
    ldr pc, _reset_h
    ldr pc, =undefined_h
    ldr pc, =sw_interrupt_h
    ldr pc, =prefetch_abort_h
    ldr pc, =data_abort_h
    ldr pc, =_reset_h
    ldr pc, =irq_h
    ldr pc, =fiq_h

    _reset_h:             .word   _reset
    undefined_h:          .word   undefined
    sw_interrupt_h:       .word   sw_interrupt
    prefetch_abort_h:     .word   prefetch_abort
    data_abort_h:         .word   data_abort
    irq_h:                .word   irq
    fiq_h:                .word   fiq

_reset:
    // Load Inetrrupt Vector
    mov     r0, #0x8000
    mov     r1, #0x0000
    ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
    stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}
    ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
    stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}

    /*
     * Kernel.img is loaded at 0x8000
     *
     * We use 0x4000000 to 0x3c00000 for stack
     *
     * Stacks:
     * 0x4000
     */

    mov r0, #0x0

    // IRQ stack
    cps #0x12
    add sp, r0, #0x4000000

    // FIQ stack
    cps #0x11
    add sp, r0, #0x3F00000

    // ABORT stack
    cps #0x17
    add sp, r0, #0x3E00000

    // SVC stck
    cps #0x13
    add sp, r0, #0x3D00000

    /*
     * Clean BSS
     *
     * If you want more information: https://en.wikipedia.org/wiki/.bss
     */
    bl bss

    /*
     * Jump to main program
     */
    bl main
    // We never reach this part of code
loop: b loop
