CC = arm-none-eabi-gcc
CFLAGS = -Wall -Werror -O2
LDFLAGS = -mcpu=arm7tdmi -mthumb -Wl,--gc-sections

all: main.gba

main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o main.o

main.gba: main.o
	$(CC) $(LDFLAGS) main.o -o main.gba

clean:
	rm -f main.o main.gba