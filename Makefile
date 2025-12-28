# Define la compilador
CC = gcc

# Define las banderas de compilación
CFLAGS = -Wall -Werror

# Define el objetivo
all: main

# Regla para compilar el archivo main.c
main: src/main.c
	$(CC) $(CFLAGS) -o main src/main.c

# Regla para limpiar los archivos objeto
clean:
	rm -f main