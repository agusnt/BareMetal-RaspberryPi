
CC = arm-none-eabi

#COPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding -g -mcpu=arm1176jzf-s
COPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding -g -mcpu=arm1176jzf-s -D RPiBplus


gcc : kernel.img

all : gcc

clean :
	rm -f *.o
	rm -f *.bin
	rm -f *.hex
	rm -f *.elf
	rm -f *.list
	rm -f *.img
	rm -f *.bc
	rm -f *.clang.opt.s

startup.o : startup.s
	$(CC)-as --warn -mcpu=arm1176jzf-s -g startup.s -o startup.o

bss.o : bss.c
	$(CC)-gcc $(COPS) -c bss.c -o bss.o

timer.o : lib/timer.c
	$(CC)-gcc $(COPS) -c lib/timer.c -o lib/timer.o

interrupt.o : lib/interrupt.c
	$(CC)-gcc $(COPS) -c lib/interrupt.c -o lib/interrupt.o

gpio.o : lib/gpio.c
	$(CC)-gcc $(COPS) -c lib/gpio.c -o lib/gpio.o

main.o : gpio.o interrupt.o main.c timer.o bss.o
	$(CC)-gcc $(COPS) -c main.c -o main.o

main.elf : memmap startup.o main.o
	$(CC)-ld -g startup.o lib/gpio.o main.o lib/interrupt.o lib/timer.o bss.o -T memmap -o main.elf

kernel.img : main.elf
	$(CC)-objcopy main.elf -O binary kernel.img
	$(CC)-objdump main.elf -S > main.diss
