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
    // Configuración de la pantalla
    *(volatile u16*)0x04000000 = MODE_3 | BG2_ENABLE;

    // Dibujar la rejilla
    for (int i = 0; i < SCREEN_H; i++) {
        for (int j = 0; j < SCREEN_W; j++) {
            if (i % 16 == 0 || j % 16 == 0) {
                // Dibujar línea de la rejilla
                ((volatile u16*)0x06000000)[i * SCREEN_W + j] = COLOR_BLANCO;
            } else {
                // Dibujar fondo negro
                ((volatile u16*)0x06000000)[i * SCREEN_W + j] = COLOR_NEGRO;
            }
        }
    }
}

// Función para borrar un cuadro
void borrarCuadro(int x, int y) {
    // Borrar solo el cuadro interior
    for (int i = y + 1; i < y + 14; i++) {
        for (int j = x + 1; j < x + 14; j++) {
            ((volatile u16*)0x06000000)[i * SCREEN_W + j] = COLOR_NEGRO;
        }
    }
}

// Función para dibujar un cuadro
void dibujarCuadro(int x, int y) {
    // Dibujar solo el cuadro interior
    for (int i = y + 1; i < y + 14; i++) {
        for (int j = x + 1; j < x + 14; j++) {
            ((volatile u16*)0x06000000)[i * SCREEN_W + j] = COLOR_BLANCO;
        }
    }
}

int main() {
    // Dibujar la rejilla una sola vez
    dibujarGrid();

    // Posición inicial del jugador
    int jugadorX = 32;
    int jugadorY = 32;

    // Dibujar el jugador inicialmente
    dibujarCuadro(jugadorX, jugadorY);

    while (1) {
        // Esperar a que se complete un frame
        while (*(volatile u16*)0x04000006 != 160);

        // Leer las teclas pulsadas
        u16 teclas = *(volatile u16*)0x04000130;

        // Mover al jugador según las teclas pulsadas
        if (teclas & KEY_LEFT) {
            borrarCuadro(jugadorX, jugadorY);
            jugadorX -= 1;
            dibujarCuadro(jugadorX, jugadorY);
        }
        if (teclas & KEY_RIGHT) {
            borrarCuadro(jugadorX, jugadorY);
            jugadorX += 1;
            dibujarCuadro(jugadorX, jugadorY);
        }
        if (teclas & KEY_UP) {
            borrarCuadro(jugadorX, jugadorY);
            jugadorY -= 1;
            dibujarCuadro(jugadorX, jugadorY);
        }
        if (teclas & KEY_DOWN) {
            borrarCuadro(jugadorX, jugadorY);
            jugadorY += 1;
            dibujarCuadro(jugadorX, jugadorY);
        }
    }

    return 0;
}
```