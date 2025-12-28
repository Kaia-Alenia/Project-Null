#include "kaia_gba.h"

int main() {
    // Código de inicialización y configuración del GBA
    *(volatile u16*)0x04000000 = MODE_3 | BG2_ENABLE;
    
    while (1) {
        // Código de bucle principal
    }
    
    return 0;
}