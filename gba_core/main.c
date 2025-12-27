#include <gba.h>

#define MODE_3 0x3
#define BG2_ENABLE 0x400

int main() {
    // Inicialización
    REG_DISPCNT = MODE_3 | BG2_ENABLE;

    // Llenar la VRAM con 0x0000 (NEGRO)
    for (volatile unsigned short* i = (volatile unsigned short*)0x06000000; i < (volatile unsigned short*)0x06000000 + 38400; i++) {
        *i = 0x0000;
    }

    while (1) {
        // Lógica del juego aquí

        // Esperar a que REG_VCOUNT sea >= 160 y < 228 para la seguridad de VSync
        while (REG_VCOUNT >= 160 && REG_VCOUNT < 228) {
            // Esperar a que se cumpla la condición
        }
    }

    return 0;
}