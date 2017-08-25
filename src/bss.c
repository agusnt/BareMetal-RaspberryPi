/**
 * Clear BSS section
 */

extern int __bss_s;
extern int __bss_e;

void bss(void){
    int *start = &__bss_s, *end = &__bss_e;
    while(start < end) *start++ = 0x0;
    return;
}
