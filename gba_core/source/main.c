#include <gba.h>

// Punteros a registros de hardware
volatile unsigned short* REG_DISPCNT = (volatile unsigned short*)0x04000000;
volatile unsigned short* PALETTE_BG = (volatile unsigned short*)0x05000000;
volatile unsigned short* VRAM_CHAR = (volatile unsigned short*)0x06000000;
volatile unsigned short* VRAM_MAP = (volatile unsigned short*)0x06000000;

// Definición de un tile simple (carita)
const unsigned int tile[] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Definición de una paleta simple
const unsigned short palette[] = {
    0x0000, // Negro
    0x7FFF, // Blanco
};

int main() {
    // Carga la paleta en la memoria de paletas de fondo
    for (int i = 0; i < 2; i++) {
        PALETTE_BG[i] = palette[i];
    }

    // Carga el tile en la memoria de caracteres (CharBlock 0)
    for (int i = 0; i < 16; i++) {
        VRAM_CHAR[i] = tile[i];
    }

    // Escribe en el mapa de fondo (ScreenBlock 8) para llenar la pantalla con ese tile
    for (int i = 0; i < 32 * 32; i++) {
        VRAM_MAP[i] = 0; // Tile 0
    }

    // Configura REG_DISPCNT para activar MODE 0 y BG0
    *REG_DISPCNT = 0x0100; // MODE 0, BG0

    // Bucle infinito
    while (1) {
        // No hacer nada
    }

    return 0;
}