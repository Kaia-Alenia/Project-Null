CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

# --- 1. ARQUITECTURA ---
# Definimos el procesador exacto de la GBA
ARCH = -mcpu=arm7tdmi -mthumb -mthumb-interwork

# --- 2. SPECS ---
# Usamos las specs nativas
SPECS = -specs=gba.specs

# --- 3. FLAGS DE COMPILACION ---
# -O2: Optimización alta, -fno-exceptions: Sin basura C++
CFLAGS = $(ARCH) $(SPECS) -O2 -Wall -ffunction-sections -fdata-sections -fno-exceptions -fno-unwind-tables

# --- 4. FLAGS DEL ENLAZADOR ---
# --gc-sections: BORRA funciones muertas
LDFLAGS = $(ARCH) $(SPECS) -Wl,--gc-sections

# --- 5. RUTAS ---
SRC = gba_core/main.c
TARGET = rom

# --- 6. REGLAS ---
all: $(TARGET).gba

$(TARGET).gba: $(TARGET).elf
 $(OBJCOPY) -O binary $(TARGET).elf $(TARGET).gba

$(TARGET).elf: $(SRC)
 $(CC) $(CFLAGS) $(LDFLAGS) $(SRC) -o $(TARGET).elf

clean:
 rm -f $(TARGET).elf $(TARGET).gba