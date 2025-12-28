CC = gcc
CFLAGS = -mcpu=arm7tdmi -O2
LDFLAGS = -mcpu=arm7tdmi -specs=gba.specs

all:
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o
	$(CC) $(LDFLAGS) src/main.o -o output.gba
clean:
	rm src/main.o output.gba