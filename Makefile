CC = gcc
CFLAGS = -Wall -Werror
TARGET = main

all: $(TARGET)

$(TARGET): src/main.c
	$(CC) $(CFLAGS) -Iinclude src/main.c -o $(TARGET)

clean:
	rm -f $(TARGET)