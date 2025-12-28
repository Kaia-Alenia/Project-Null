# Makefile Maestro para GBA
CROSS   := arm-none-eabi-
CC      := $(CROSS)gcc
OBJCOPY := $(CROSS)objcopy

ARCH    := -mthumb-interwork -mthumb
SPECS   := -specs=gba.specs

CFLAGS  := $(ARCH) -O2 -Wall -fno-strict-aliasing -Iinclude
LDFLAGS := $(ARCH) $(SPECS)

.PHONY: all clean

all: game.gba

game.gba: game.elf
	$(OBJCOPY) -O binary $< $@

game.elf: src/main.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f *.elf *.gba
