```c
#include "kaia_gba.h"

#define TILE_SIZE 16

// Variables para el jugador
int jugador_x = 0;
int jugador_y = 0;

// Variable para detectar flancos de subida
u16 old_keys;

void dibujarGrid() {
    for (int i = 0; i < 240; i += TILE_SIZE) {
        // Dibujar líneas horizontales
        for (int j = 0; j < 160; j++) {
            plotPixel(j, i, 0x4210);
        }
    }
    for (int i = 0; i < 160; i += TILE_SIZE) {
        // Dibujar líneas verticales
        for (int j = 0; j < 240; j++) {
            plotPixel(i, j, 0x4210);
        }
    }
}

int main() {
    while (1) {
        // Limpiar la pantalla
        fillScreen(0x0000);

        // Llamar a la función para dibujar el grid
        dibujarGrid();

        // Dibujar al jugador
        // ...

        // Obtener las teclas presionadas
        old_keys = keys;
        keys = keypad();

        // Detección de "Key Down" para los botones de movimiento
        if ((~old_keys & keys) & KEY_LEFT) {
            // Mover al jugador hacia la izquierda
            jugador_x -= TILE_SIZE;
        }
        if ((~old_keys & keys) & KEY_RIGHT) {
            // Mover al jugador hacia la derecha
            jugador_x += TILE_SIZE;
        }
        if ((~old_keys & keys) & KEY_UP) {
            // Mover al jugador hacia arriba
            jugador_y -= TILE_SIZE;
        }
        if ((~old_keys & keys) & KEY_DOWN) {
            // Mover al jugador hacia abajo
            jugador_y += TILE_SIZE;
        }

        // Actualizar la pantalla
        vid_vsync();
    }
    return 0;
}