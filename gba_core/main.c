#include "kaia_gba.h"

int main() {
    // Inicializar la pantalla con color negro
    for (int i = 0; i < 240 * 160; i++) {
        VRAM[i] = 0x0000; // Color negro
    }

    while (1) {
        // Llamar a la función vid_vsync para sincronizar con la pantalla
        vid_vsync();
    }

    return 0;
}