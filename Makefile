CC = arm-none-eabi-gcc
CFLAGS = -Wall -Wextra -O2 -mcpu=arm7tdmi -mthumb-interwork
LDFLAGS = -mcpu=arm7tdmi -mthumb-interwork

main.elf: main.o
	$(CC) $(LDFLAGS) -o $@ $^

main.o: src/main.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f main.elf main.o