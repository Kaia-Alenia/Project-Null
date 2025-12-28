CC = arm-none-eabi-gcc
CFLAGS = -Wall -Werror -O2
LDFLAGS = -nostartfiles

all: main.elf

main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o main.o

main.elf: main.o
	$(CC) $(LDFLAGS) main.o -o main.elf

clean:
	rm -f main.o main.elf