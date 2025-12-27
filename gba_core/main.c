#include <gba.h>

int main() {
    // Configuración del modo 3
    REG_DISPCNT = MODE_3 | BG2_ENABLE;

    // Configuración del color rojo para la pantalla
    u16* videoBuffer = (u16*)0x06000000;
    for (int i = 0; i < 240 * 160; i++) {
        videoBuffer[i] = RGB(31, 0, 0);
    }

    while (1) {
        // Bucle infinito para mantener la pantalla roja
    }

    return 0;
}