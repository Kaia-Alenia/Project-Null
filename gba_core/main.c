#include "kaia_gba.h"
#define NEGRO 0x0000
#define AZUL  0x7C00

// --- IMPLEMENTACIÓN DE FUNCIONES (Deben estar aquí) ---
void vid_vsync() {
    while(REG_VCOUNT >= 160);
    while(REG_VCOUNT < 160);
}

void dibujarJugador(int x, int y, int color) {
    for(int i = 0; i < 16; i++) {
        for(int j = 0; j < 16; j++) {
            VRAM[(y + j) * 240 + (x + i)] = color;
        }
    }
}

// --- MAIN ---
int main() {
    REG_DISPCNT = MODE_3 | BG2_ENABLE;
    int x = 120, y = 80;
    while(1) {
        vid_vsync();
        dibujarJugador(x, y, AZUL);
    }
    return 0;
}