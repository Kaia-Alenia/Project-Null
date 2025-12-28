CC = gcc
CFLAGS = -Wall -Wextra -O2 -march=armv4t -mtune=arm7tdmi
LDFLAGS = -nostartfiles

all: main.o
	$(CC) $(LDFLAGS) -o main.elf main.o

main.o: src/main.c include/kaia_gba.h
	$(CC) $(CFLAGS) -c src/main.c -o main.o

clean:
	rm -f main.o main.elf