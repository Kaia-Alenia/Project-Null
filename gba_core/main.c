#include "kaia_gba.h"

// Definir colores
#define NEGRO 0x0000
#define BLANCO 0xFFFF
#define AZUL 0x7C00

// Variables del jugador
int posX = 120;
int posY = 80;

int main() {
    // Activar el MODO 3
    REG_DISPCNT = MODE_3 | BG2_ENABLE;

    while (1) {
        // Lectura de Inputs
        if (!(REG_KEYINPUT & KEY_UP)) {
            posY--;
        }
        if (!(REG_KEYINPUT & KEY_DOWN)) {
            posY++;
        }
        if (!(REG_KEYINPUT & KEY_LEFT)) {
            posX--;
        }
        if (!(REG_KEYINPUT & KEY_RIGHT)) {
            posX++;
        }

        // Limpiar pantalla
        for (int i = 0; i < 38400; i++) {
            VRAM[i] = NEGRO;
        }

        // Dibujar jugador
        for (int y = 0; y < 16; y++) {
            for (int x = 0; x < 16; x++) {
                VRAM[(posY + y) * 240 + (posX + x)] = AZUL;
            }
        }

        // Retardo
        for (int i = 0; i < 10000; i++) {
            // Bucle vacío para retrasar el movimiento
        }
    }

    return 0;
}