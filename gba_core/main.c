```c
#include "kaia_gba.h"

// Definición de constantes
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

// Definición de colores
#define GRIS 0x8888
#define NEGRO 0x0000

// Función para restaurar una casilla
void restaurarCasilla(int x, int y) {
    // Dibujar bordes grises
    for (int i = 0; i < 10; i++) {
        ((volatile unsigned short*)0x06000000)[(y * 10) + i + (x * 10 * 160)] = GRIS;
        ((volatile unsigned short*)0x06000000)[(y * 10) + i + ((x * 10 + 9) * 160)] = GRIS;
    }
    for (int i = 0; i < 10; i++) {
        ((volatile unsigned short*)0x06000000)[(y * 10) + (x * 160)] = GRIS;
        ((volatile unsigned short*)0x06000000)[((y * 10 + 9)) + (x * 160)] = GRIS;
    }
    // Dibujar centro negro
    for (int i = 1; i < 9; i++) {
        for (int j = 1; j < 9; j++) {
            ((volatile unsigned short*)0x06000000)[(y * 10 + i) + ((x * 10 + j) * 160)] = NEGRO;
        }
    }
}

// Función para dibujar la grilla completa
void dibujarGridCompleto() {
    for (int i = 0; i < SCREEN_H; i++) {
        for (int j = 0; j < SCREEN_W; j++) {
            if ((i / 10) % 2 == (j / 10) % 2) {
                ((volatile unsigned short*)0x06000000)[i + j * 160] = GRIS;
            } else {
                ((volatile unsigned short*)0x06000000)[i + j * 160] = NEGRO;
            }
        }
    }
}

int main() {
    // Configuración inicial
    *(volatile unsigned short*)0x04000000 = MODE_3 | BG2_ENABLE;
    dibujarGridCompleto();

    int jugadorX = 0;
    int jugadorY = 0;
    int monedaX = 5;
    int monedaY = 5;

    while (1) {
        // Restaurar casillas antes de mover al jugador o la moneda
        restaurarCasilla(jugadorX, jugadorY);
        restaurarCasilla(monedaX, monedaY);

        // Mover al jugador o la moneda
        if (*(volatile unsigned short*)0x04000130 & KEY_RIGHT) {
            jugadorX++;
        }
        if (*(volatile unsigned short*)0x04000130 & KEY_LEFT) {
            jugadorX--;
        }
        if (*(volatile unsigned short*)0x04000130 & KEY_UP) {
            jugadorY--;
        }
        if (*(volatile unsigned short*)0x04000130 & KEY_DOWN) {
            jugadorY++;
        }

        // Dibujar al jugador o la moneda
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                ((volatile unsigned short*)0x06000000)[(jugadorY * 10 + i) + ((jugadorX * 10 + j) * 160)] = 0x000F;
                ((volatile unsigned short*)0x06000000)[(monedaY * 10 + i) + ((monedaX * 10 + j) * 160)] = 0x00FF;
            }
        }

        // Esperar a la siguiente vsync
        while (*(volatile unsigned short*)0x04000006 != 160);
    }

    return 0;
}
```