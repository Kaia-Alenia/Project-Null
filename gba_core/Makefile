# Configuración del compilador
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld

# Configuración de los flags del compilador
CFLAGS = -O2 -Wall -Werror
ASFLAGS = -O2
LDFLAGS = -O2

# Archivos fuente
SRC = main.c

# Archivos objeto
OBJ = $(SRC:.c=.o)

# Regla para compilar el archivo principal
all: $(OBJ)
	$(LD) $(LDFLAGS) -o main.gba $(OBJ)