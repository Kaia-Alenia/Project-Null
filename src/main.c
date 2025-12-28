#include "kaia_gba.h"

int main() {
    // Inicialización del modo de video
    *(volatile u16*)0x04000000 = MODE_3 | BG2_ENABLE;

    // Bucle principal
    while (1) {
        // Leer la entrada del teclado
        u16 keys = *(volatile u16*)0x04000130;

        // Manejar la entrada del teclado
        if (keys & KEY_A) {
            // Acción cuando se presiona la tecla A
        }

        // Actualizar la pantalla
        *(volatile u16*)0x04000006 = 0;
    }

    return 0;
}