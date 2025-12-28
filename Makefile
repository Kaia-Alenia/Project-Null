CC = gcc
CFLAGS = -Wall -Werror
TARGET = main

all: $(TARGET)

$(TARGET): src/main.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)