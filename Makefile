TARGET := proyecto_gba
SOURCES := source/main.c
OBJECTS := $(SOURCES:.c=.o)

CC := arm-none-eabi-gcc
AS := arm-none-eabi-as
LD := arm-none-eabi-ld
OBJCOPY := arm-none-eabi-objcopy

CFLAGS := -mthumb -mthumb-interwork -O2 -Wall -Wextra
LDFLAGS := -mthumb -mthumb-interwork -Wl,--gc-sections
LIBS := -lnds9

all: $(TARGET).gba

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

$(TARGET).gba: $(TARGET).elf
	$(OBJCOPY) -v -O binary $< $@

clean:
	rm -f $(OBJECTS) $(TARGET).elf $(TARGET).gba

.PHONY: all clean