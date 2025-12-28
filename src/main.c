#include "kaia_gba.h"

int main() {
    // Inicialización del modo de video
    *(volatile u16*)0x04000000 = MODE_3 | BG2_ENABLE;

    // Bucle principal
    while (1) {
        // Lee el estado de los botones
        u16 keys = *(volatile u16*)0x04000130;

        // Verifica si se presionó el botón A
        if (keys & KEY_A) {
            // Acción cuando se presiona el botón A
        }

        // Verifica si se presionó el botón B
        if (keys & KEY_B) {
            // Acción cuando se presiona el botón B
        }

        // Verifica si se presionó el botón derecho
        if (keys & KEY_RIGHT) {
            // Acción cuando se presiona el botón derecho
        }

        // Verifica si se presionó el botón izquierdo
        if (keys & KEY_LEFT) {
            // Acción cuando se presiona el botón izquierdo
        }

        // Verifica si se presionó el botón arriba
        if (keys & KEY_UP) {
            // Acción cuando se presiona el botón arriba
        }

        // Verifica si se presionó el botón abajo
        if (keys & KEY_DOWN) {
            // Acción cuando se presiona el botón abajo
        }
    }

    return 0;
}