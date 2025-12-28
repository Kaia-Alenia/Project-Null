CC = gcc
CFLAGS = -Wall -O2
LDFLAGS = 
TARGET = proyecto_gba.gba

all: $(TARGET)

$(TARGET): src/main.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET)