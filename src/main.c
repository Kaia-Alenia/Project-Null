#include "kaia_gba.h"

int main() {
    // Inicializar el modo de pantalla
    *(volatile unsigned short*)0x04000000 = MODE_3 | BG2_ENABLE;

    // Bucle principal
    while (1) {
        // Leer estado de teclas
        unsigned short teclas = *(volatile unsigned short*)0x04000130;

        // Revisar si se presiona la tecla A
        if (teclas & KEY_A) {
            // Acción al presionar la tecla A
        }

        // Esperar a que se actualice la pantalla
        while (*(volatile unsigned short*)0x04000006 != 160);
    }

    return 0;
}