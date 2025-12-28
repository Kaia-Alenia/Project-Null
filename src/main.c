#include "kaia_gba.h"

int main() {
    // Inicialización de la pantalla
    *(volatile unsigned short*)0x04000000 = MODE_3 | BG2_ENABLE;

    while (1) {
        // Bucle principal
    }

    return 0;
}