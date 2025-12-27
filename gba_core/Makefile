# Makefile para el proyecto GBA
TARGET := gba_core
CC := arm-none-eabi-gcc
AS := arm-none-eabi-as
LD := arm-none-eabi-ld
OBJCOPY := arm-none-eabi-objcopy

# Ruta de los archivos de código fuente
SRC_DIR := source
INC_DIR := include

# Archivos de código fuente
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:.c=.o)

# Opciones de compilación
CFLAGS := -mcpu=arm7tdmi -O2 -Wall -Wextra
ASFLAGS := -mcpu=arm7tdmi
LDFLAGS := -mcpu=arm7tdmi -Wl,-Map,$(TARGET).map

# Regla para compilar el ejecutable
$(TARGET).elf: $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

# Regla para compilar los archivos de código fuente
%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Regla para crear el archivo binario
$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

# Regla para limpiar los archivos objeto y el ejecutable
clean:
	rm -f $(OBJ) $(TARGET).elf $(TARGET).bin