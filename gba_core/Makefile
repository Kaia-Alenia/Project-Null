# Herramientas
CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

# Nombre del proyecto
NAME    = rom

# Flags de compilación para GBA
CFLAGS  = -mthumb -mthumb-interwork -O2 -Wall -specs=gba.specs

# Regla por defecto
all: $(NAME).gba

# Regla para crear el binario final (IMPORTANTE: La linea de abajo necesita TAB)
$(NAME).gba: $(NAME).elf
	$(OBJCOPY) -O binary $(NAME).elf $(NAME).gba

# Regla para compilar el codigo C (IMPORTANTE: La linea de abajo necesita TAB)
$(NAME).elf: main.c
	$(CC) $(CFLAGS) main.c -o $(NAME).elf

# Limpieza
clean:
	rm -f *.elf *.gba
