# --- TRUCO ANTI-ERROR DE FORMATO ---
# Usamos '>' como tabulador para evitar el error 'missing separator'
.RECIPEPREFIX = >

CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

# --- CONFIGURACION ---
ARCH = -mcpu=arm7tdmi -mthumb -mthumb-interwork
SPECS = -specs=gba.specs

# Flags optimizados para evitar overflow de memoria
CFLAGS = $(ARCH) $(SPECS) -O2 -Wall -ffunction-sections -fdata-sections -fno-exceptions -fno-unwind-tables
LDFLAGS = $(ARCH) $(SPECS) -Wl,--gc-sections

SRC = gba_core/main.c
TARGET = rom

# --- REGLAS ---
all: $(TARGET).gba

$(TARGET).gba: $(TARGET).elf
> $(OBJCOPY) -O binary $(TARGET).elf $(TARGET).gba

$(TARGET).elf: $(SRC)
> $(CC) $(CFLAGS) $(LDFLAGS) $(SRC) -o $(TARGET).elf

clean:
> rm -f $(TARGET).elf $(TARGET).gba