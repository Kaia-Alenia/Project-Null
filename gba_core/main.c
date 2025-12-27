```c
#include "kaia_gba.h"

// Definiciones de constantes
#define MODE_3 0x0003
#define BG2_ENABLE 0x0400
#define SCREEN_W 240
#define SCREEN_H 160
#define KEY_A 0x0001
#define KEY_B 0x0002
#define KEY_RIGHT 0x0010
#define KEY_LEFT 0x0020
#define KEY_UP 0x0040
#define KEY_DOWN 0x0080

// Definiciones de colores
#define COLOR_NEGRO 0x0000
#define COLOR_BLANCO 0xFFFF

// Función para dibujar la rejilla
void dibujarGrid() {
    u16* vram = (u16*)0x06000000;
    for (int y = 0; y < SCREEN_H; y++) {
        for (int x = 0; x < SCREEN_W; x++) {
            if (x % 16 == 0 || y % 16 == 0) {
                vram[y * SCREEN_W + x] = COLOR_BLANCO;
            } else {
                vram[y * SCREEN_W + x] = COLOR_NEGRO;
            }
        }
    }
}

// Función para borrar un cuadro
void borrarCuadro(int x, int y) {
    u16* vram = (u16*)0x06000000;
    for (int dy = 0; dy < 14; dy++) {
        for (int dx = 0; dx < 14; dx++) {
            vram[(y + dy) * SCREEN_W + x + dx] = COLOR_NEGRO;
        }
    }
}

// Función para dibujar un cuadro
void dibujarCuadro(int x, int y) {
    u16* vram = (u16*)0x06000000;
    for (int dy = 0; dy < 14; dy++) {
        for (int dx = 0; dx < 14; dx++) {
            vram[(y + dy) * SCREEN_W + x + dx] = COLOR_BLANCO;
        }
    }
}

int main() {
    // Configuración inicial
    *(volatile u16*)0x04000000 = MODE_3 | BG2_ENABLE;

    // Dibujar la rejilla
    dibujarGrid();

    // Posición inicial del jugador
    int jugadorX = 10;
    int jugadorY = 10;

    // Dibujar al jugador
    dibujarCuadro(jugadorX, jugadorY);

    while (1) {
        // Esperar a que se complete el frame
        while (*(volatile u16*)0x04000006 != 160);

        // Leer las teclas presionadas
        u16 teclas = *(volatile u16*)0x04000130;

        // Mover al jugador
        if (teclas & KEY_LEFT) {
            borrarCuadro(jugadorX, jugadorY);
            jugadorX -= 1;
            if (jugadorX < 0) jugadorX = 0;
            dibujarCuadro(jugadorX, jugadorY);
        }
        if (teclas & KEY_RIGHT) {
            borrarCuadro(jugadorX, jugadorY);
            jugadorX += 1;
            if (jugadorX > SCREEN_W - 14) jugadorX = SCREEN_W - 14;
            dibujarCuadro(jugadorX, jugadorY);
        }
        if (teclas & KEY_UP) {
            borrarCuadro(jugadorX, jugadorY);
            jugadorY -= 1;
            if (jugadorY < 0) jugadorY = 0;
            dibujarCuadro(jugadorX, jugadorY);
        }
        if (teclas & KEY_DOWN) {
            borrarCuadro(jugadorX, jugadorY);
            jugadorY += 1;
            if (jugadorY > SCREEN_H - 14) jugadorY = SCREEN_H - 14;
            dibujarCuadro(jugadorX, jugadorY);
        }
    }

    return 0;
}
```