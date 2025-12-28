CC = arm-none-eabi-gcc
CFLAGS = -mcpu=arm7tdmi -O2 -Wall
LDFLAGS = -mcpu=arm7tdmi -Wl,--gc-sections

all: src/main.o
	$(CC) $(CFLAGS) -o output.elf src/main.o

src/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c

clean:
	rm -f src/main.o output.elf