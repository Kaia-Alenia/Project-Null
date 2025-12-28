CC = arm-none-eabi-gcc
CFLAGS = -Wall -Werror -O2
LDFLAGS = -nostartfiles -Wl,--gc-sections

game.elf: src/main.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o game.elf src/main.o

src/main.o: src/main.c include/kaia_gba.h
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

clean:
	rm -f src/main.o game.elf