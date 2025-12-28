#include "kaia_gba.h"

int main() {
    // Configuramos el modo de pantalla
    *(volatile unsigned short*)0x04000000 = MODE_3 | BG2_ENABLE;

    // Pintamos la pantalla de un color (azul en este caso)
    for (int i = 0; i < SCREEN_W * SCREEN_H; i++) {
        ((unsigned short*)0x06000000)[i] = 0x001F; // Azul
    }

    while (1) {
        // Bucle infinito para mantener la pantalla pintada
    }

    return 0;
}