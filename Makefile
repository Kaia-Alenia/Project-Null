CC = arm-none-eabi-gcc
CFLAGS = -mcpu=arm7tdmi -O2 -Wall
LDFLAGS = -mcpu=arm7tdmi -Wl,--gc-sections

main.o: src/main.c
    $(CC) $(CFLAGS) -c src/main.c -o main.o

main: main.o
    $(CC) $(LDFLAGS) main.o -o main