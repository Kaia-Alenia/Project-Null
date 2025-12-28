CC = arm-none-eabi-gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -nostartfiles

game.elf: src/main.o
	$(CC) $(LDFLAGS) -o game.elf src/main.o

src/main.o: src/main.c include/kaia_gba.h
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

clean:
	rm -f src/main.o game.elf