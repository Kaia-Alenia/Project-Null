CC = arm-none-eabi-gcc
CFLAGS = -Wall -Werror -O2
LDFLAGS = -nostdlib

all: src/main.o
	$(CC) $(LDFLAGS) -o output.elf src/main.o

src/main.o: src/main.c include/kaia_gba.h
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

clean:
	rm -f src/main.o output.elf