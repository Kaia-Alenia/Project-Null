#include "kaia_gba.h"

// DEFINICIONES QUE BORRASTE
#define NEGRO 0x0000
#define AZUL  0x7C00

// IMPLEMENTACIÓN COMPLETA (Sin prototipos en el header)
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

int main() {
    REG_DISPCNT = MODE_3 | BG2_ENABLE;
    int x = 120, y = 80;

    // Limpiar pantalla al inicio
    for(int i=0; i<38400; i++) VRAM[i] = NEGRO;

    while (1) {
        dibujarJugador(x, y, NEGRO); // Borrar

        if (!(REG_KEYINPUT & KEY_RIGHT)) x++;
        if (!(REG_KEYINPUT & KEY_LEFT))  x--;
        if (!(REG_KEYINPUT & KEY_UP))    y--;
        if (!(REG_KEYINPUT & KEY_DOWN))  y++;

        dibujarJugador(x, y, AZUL);  // Pintar
        vid_vsync();
    }
    return 0;
}