CC = arm-none-eabi-gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -nostartfiles -Wl,--gc-sections

all: main.gba

main.gba: src/main.o
	$(CC) $(LDFLAGS) -o $@ $^

src/main.o: src/main.c include/kaia_gba.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f src/main.o main.gba