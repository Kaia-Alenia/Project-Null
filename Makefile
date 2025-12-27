# Configuración del compilador
CC = arm-none-eabi-gcc
CFLAGS = -Wall -Werror -O2 -mcpu=arm7tdmi -mthumb-interwork -ffreestanding -nostdlib
CFLAGS += -fdata-sections -ffunction-sections -Wl,--gc-sections

# Configuración del enlazador
LDFLAGS = -T gba.ld -Wl,--gc-sections

# Reglas de compilación
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para la construcción del ejecutable
gba.elf: main.o
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

# Regla para la generación del archivo binario
gba.gba: gba.elf
	arm-none-eabi-objcopy -O binary $< $@

# Regla para limpiar los archivos temporales
clean:
	rm -f *.o gba.elf gba.gba

# Regla por defecto
all: gba.gba