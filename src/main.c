#include "kaia_gba.h"

int main() {
    // Inicializar la pantalla
    *(volatile u16*)0x04000000 = MODE_3 | BG2_ENABLE;

    while (1) {
        // Leer la entrada del teclado
        u16 keys = *(volatile u16*)0x04000130;

        // Verificar si se presiona la tecla A
        if (keys & KEY_A) {
            // Acción cuando se presiona la tecla A
        }
    }

    return 0;
}