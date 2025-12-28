makefile
CC = gcc
CFLAGS = -Wall -Werror
LDFLAGS = -lgcc
TARGET = main.gba

all: $(TARGET)

$(TARGET): src/main.o
	$(CC) $(LDFLAGS) -o $@ $^

src/main.o: src/main.c include/kaia_gba.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o $(TARGET)