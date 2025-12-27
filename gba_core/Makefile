# Herramientas
CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

# Nombre del juego
NAME    = rom

# Flags de compilación para GBA (Arquitectura ARM7TDMI)
CFLAGS  = -mthumb -mthumb-interwork -O2 -Wall -specs=gba.specs

# Regla principal
all: $(NAME).gba

# Crear el archivo .gba desde el .elf
$(NAME).gba: $(NAME).elf
 $(OBJCOPY) -O binary $(NAME).elf $(NAME).gba

# Compilar main.c y crear el ejecutable .elf
$(NAME).elf: main.c
 $(CC) $(CFLAGS) main.c -o $(NAME).elf

clean:
 rm -f *.elf *.gba