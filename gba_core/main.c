#include "kaia_gba.h"

// Función para espera de VSync
void vid_vsync() {
    while(REG_VCOUNT < 160);
}

int main() {
    // Inicializa REG_DISPCNT
    REG_DISPCNT = MODE_0 | BG0_ON;

    while(1) {
        // Lógica de movimiento
        // Aquí va tu lógica de juego o movimiento

        // Llama a vid_vsync() al final del bucle
        vid_vsync();
    }

    return 0;
}