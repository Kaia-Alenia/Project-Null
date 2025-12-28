CC = gcc
CFLAGS = -Wall -O2
LDFLAGS = -mthumb-interwork -Wl,--map
TARGET = proyecto_gba.gba

all: $(TARGET)

$(TARGET): src/main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

src/main.o: src/main.c include/kaia_gba.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)