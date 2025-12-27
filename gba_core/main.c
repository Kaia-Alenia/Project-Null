#include "kaia_gba.h"

// Definición de colores en 15-bit
#define COLOR_GRID 0x3186
#define COLOR_PLAYER 0x7E0

// Variables para la posición del jugador
u16 playerX = 10;
u16 playerY = 10;

int main() {
    // Configuración inicial de la pantalla
    REG_DISPCNT = MODE_3 | BG2_ENABLE;

    // Dibujar la rejilla una vez
    for (u16 y = 0; y < 160; y += 10) {
        for (u16 x = 0; x < 240; x += 10) {
            // Dibujar línea horizontal
            for (u16 i = 0; i < 10; i++) {
                *(volatile u16*)(0x06000000 + (y * 240) + x + i) = COLOR_GRID;
            }
            // Dibujar línea vertical
            for (u16 i = 0; i < 10; i++) {
                *(volatile u16*)(0x06000000 + ((y + i) * 240) + x) = COLOR_GRID;
            }
        }
    }

    // Bucle principal
    while (1) {
        // Esperar a que se complete el frame
        while (REG_VCOUNT < 160);

        // Leer entrada del usuario
        u16 keys = REG_KEYINPUT;

        // Mover al jugador según la entrada
        if (keys & KEY_LEFT) {
            playerX -= 1;
        }
        if (keys & KEY_RIGHT) {
            playerX += 1;
        }
        if (keys & KEY_UP) {
            playerY -= 1;
        }
        if (keys & KEY_DOWN) {
            playerY += 1;
        }

        // Dibujar al jugador en la nueva posición
        for (u16 y = 0; y < 10; y++) {
            for (u16 x = 0; x < 10; x++) {
                *(volatile u16*)(0x06000000 + ((playerY + y) * 240) + playerX + x) = COLOR_PLAYER;
            }
        }
    }

    return 0;
}