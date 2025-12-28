CC = arm-none-eabi-gcc
CFLAGS = -Wall -Werror -O2
LDFLAGS = -nostartfiles -Wl,--gc-sections

all: main.gba

main.gba: src/main.o
	$(CC) $(LDFLAGS) -o $@ $^

src/main.o: src/main.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f src/main.o main.gba