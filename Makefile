# File:   Makefile
# Author: Courteney Brownie (cjb261) and Sara Dyson (sed65)
# Date:   11 Oct 2016
# Descr:  Makefile

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I../../drivers -I../../fonts -I../../drivers/avr -I../../utils
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: main.out


# Compile: create object files from C source files.
main.o: main.c ../../drivers/avr/system.h ../../drivers/avr/ir_uart.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

ir_uart.o: ../../drivers/avr/ir_uart.c ../../drivers/avr/ir_uart.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/avr/timer0.h ../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

usart1.o: ../../drivers/avr/usart1.c ../../drivers/avr/system.h ../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

timer0.o: ../../drivers/avr/timer0.c ../../drivers/avr/bits.h ../../drivers/avr/prescale.h ../../drivers/avr/system.h ../../drivers/avr/timer0.h
	$(CC) -c $(CFLAGS) $< -o $@

prescale.o: ../../drivers/avr/prescale.c ../../drivers/avr/prescale.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: ../../drivers/navswitch.c ../../drivers/avr/delay.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/navswitch.h
	$(CC) -c $(CFLAGS) $< -o $@

pacer.o: ../../utils/pacer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h ../../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

tinygl.o: ../../utils/tinygl.c ../../drivers/avr/system.h ../../drivers/display.h ../../utils/font.h ../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@

font.o: ../../utils/font.c ../../drivers/avr/system.h ../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@

display.o: ../../drivers/display.c ../../drivers/avr/system.h ../../drivers/display.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

ledmat.o: ../../drivers/ledmat.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: ../../drivers/avr/timer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

matrix.o: matrix.c ../../drivers/avr/system.h ../../drivers/avr/pio.h ../../utils/pacer.h struct.h traffic.h matrix.h
	$(CC) -c $(CFLAGS) $< -o $@

navigation.o: navigation.c ../../drivers/avr/system.h ../../drivers/navswitch.h global.h navigation.h
	$(CC) -c $(CFLAGS) $< -o $@

message.o: message.c ../../drivers/avr/system.h ../../fonts/font5x7_1.h ../../utils/pacer.h ../../utils/tinygl.h ../../utils/uint8toa.h message.h
	$(CC) -c $(CFLAGS) $< -o $@

traffic.o: traffic.c ../../drivers/avr/system.h ../../drivers/avr/timer.h struct.h traffic.h
	$(CC) -c $(CFLAGS) $< -o $@

player.o: player.c ../../drivers/avr/system.h struct.h traffic.h player.h
	$(CC) -c $(CFLAGS) $< -o $@

game.o: game.c ../../drivers/avr/system.h struct.h player.h navigation.h traffic.h matrix.h game.h global.h
	$(CC) -c $(CFLAGS) $< -o $@

time.o: time.c ../../drivers/avr/system.h ../../drivers/avr/timer.h time.h global.h
	$(CC) -c $(CFLAGS) $< -o $@

uint8toa.o: ../../utils/uint8toa.c ../../drivers/avr/system.h ../../utils/uint8toa.h
	$(CC) -c $(CFLAGS) $< -o $@

# Link: create ELF output file from object files.
main.out: main.o pio.o system.o navswitch.o pacer.o tinygl.o font.o display.o ledmat.o timer.o matrix.o navigation.o message.o traffic.o player.o game.o time.o uint8toa.o ir_uart.o timer0.o usart1.o prescale.o uint8toa.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean:
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: main.out
	$(OBJCOPY) -O ihex main.out main.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash main.hex; dfu-programmer atmega32u2 start
