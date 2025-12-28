# --- MAKEFILE CORRECTO PARA GBA (DevkitPro) ---

# 1. Definimos las herramientas de compilación correctas (NO USAR GCC A SECAS)
CROSS   := arm-none-eabi-
CC      := $(CROSS)gcc
OBJCOPY := $(CROSS)objcopy

# 2. Flags para el procesador ARM7TDMI (El cerebro de la GBA)
ARCH    := -mthumb-interwork -mthumb
SPECS   := -specs=gba.specs

# 3. Opciones de compilación
# -O2: Optimizar velocidad
# -Wall: Mostrar advertencias
# -Iinclude: Buscar archivos .h en la carpeta include/
CFLAGS  := $(ARCH) -O2 -Wall -fno-strict-aliasing -Iinclude

# 4. Opciones de Linker (Empaquetado)
LDFLAGS := $(ARCH) $(SPECS)

.PHONY: all clean

# --- REGLAS DE CONSTRUCCIÓN ---

# El objetivo final es el archivo .gba
all: game.gba

# Paso 2: Convertir el ejecutable .elf a formato cartucho .gba
game.gba: game.elf
	$(OBJCOPY) -O binary $< $@

# Paso 1: Compilar el código C (src/main.c) a ejecutable .elf
game.elf: src/main.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

# Limpieza
clean:
	rm -f *.elf *.gba
