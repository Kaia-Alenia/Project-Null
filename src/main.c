#include "kaia_gba.h"

int main() {
    // Inicializar el modo de video
    *(volatile u16*)0x04000000 = MODE_3 | BG2_ENABLE;

    // Inicializar la pantalla
    for (int i = 0; i < SCREEN_W * SCREEN_H; i++) {
        ((u16*)0x06000000)[i] = 0x0000; // Color negro
    }

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