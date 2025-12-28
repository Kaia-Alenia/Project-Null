#include "kaia_gba.h"
// main.c - Prueba de fuego para GBA
typedef unsigned short u16;

// Registros de memoria de la GBA
#define REG_DISPCNT  (*(volatile u16*)0x04000000)
#define VRAM         ((volatile u16*)0x06000000)

// Configuración de video (Modo 3 = Bitmap de colores)
#define MODE_3       0x0003
#define BG2_ENABLE   0x0400

// Color Rojo puro (5 bits por canal: 00000 00000 11111)
#define COLOR_RED    0x001F

int main() {
    // 1. Encendemos la pantalla
    REG_DISPCNT = MODE_3 | BG2_ENABLE;

    // 2. Llenamos la memoria de video con color rojo
    // La pantalla tiene 240x160 píxeles = 38,400 píxeles
    for (int i = 0; i < 240 * 160; i++) {
        VRAM[i] = COLOR_RED;
    }

    // 3. Bucle infinito para que no se apague
    while (1) {}

    return 0;
}
