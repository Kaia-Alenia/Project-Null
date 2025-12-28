CC = arm-none-eabi-gcc
CFLAGS = -Wall -Werror
LDFLAGS = 

src/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

clean:
	rm -f src/main.o