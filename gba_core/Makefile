TARGET := mi_juego_gba
SOURCES := .
INCLUDES := ..

CC := arm-eabi-gcc
AS := arm-eabi-as
LD := arm-eabi-ld
OBJCOPY := arm-eabi-objcopy

CFLAGS := -mthumb -mthumb-interwork -O2 -Wall
LDFLAGS := -mthumb -mthumb-interwork -Wl,--gc-sections

all:
	$(CC) $(CFLAGS) -c $(SOURCES)/*.c
	$(LD) $(LDFLAGS) -o $(TARGET).elf *.o
	$(OBJCOPY) $(TARGET).elf $(TARGET).gba