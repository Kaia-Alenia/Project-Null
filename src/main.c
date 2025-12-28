#include "kaia_gba.h"

int main() {
    // Inicialización del modo 3
    *(volatile unsigned short*)0x04000000 = 0x0003 | 0x0400;

    while(1) {
        // Bucle principal
    }

    return 0;
}