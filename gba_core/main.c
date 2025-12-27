#include "kaia_gba.h"

void vid_vsync() {
    while (REG_VCOUNT >= 160); // Espera a que la pantalla termine de dibujarse
}

int main() {
    // Inicialización de la pantalla
    REG_DISPCNT = MODE_3 | BG2_ENABLE;

    u16 color = 0x7FFF; // Color blanco

    // Dibujar en la pantalla utilizando VRAM
    for (int i = 0; i < 240 * 160; i++) {
        VRAM[i] = color;
    }

    while (1) {
        vid_vsync();
    }

    return 0;
}