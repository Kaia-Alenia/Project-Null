CC = arm-none-eabi-gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -nostartfiles

all: src/main.o
    $(CC) $(LDFLAGS) -o output.elf src/main.o

src/main.o: src/main.c
    $(CC) $(CFLAGS) -c src/main.c -o src/main.o

clean:
    rm -f src/main.o output.elf