CC = arm-none-eabi-gcc
CFLAGS = -Wall -Werror -O2
LDFLAGS = -mcpu=arm7tdmi -mthumb -mthumb-interwork

main.elf: main.o
	$(CC) $(LDFLAGS) -o $@ $^

main.o: src/main.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f main.elf main.o