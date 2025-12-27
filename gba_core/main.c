#include <gba.h>

int main() {
    // Inicializa el modo de video
    REG_DISPCTL = MODE_0 | BG0_ENABLE;

    // Inicializa el fondo
    u16* fondo = (u16*)0x06000000;
    for (int i = 0; i < 240 * 160; i++) {
        fondo[i] = RGB(0, 0, 0);
    }

    // Bucle principal
    while (1) {
        // Actualiza el fondo
        for (int i = 0; i < 240 * 160; i++) {
            fondo[i] = RGB(255, 255, 255);
        }

        // Espera un vblank
        while (!(REG_VCOUNT & 1));
    }

    return 0;
}