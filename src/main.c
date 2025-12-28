#include "include/kaia_gba.h"

int main() {
    // Configuración inicial del modo de pantalla
    *(volatile unsigned short*)0x04000000 = 0x0003; // Modo 3

    // Bucle principal
    while (1) {
        // Lee el estado de los botones
        unsigned short keys = *(volatile unsigned short*)0x04000130;

        // Verifica si se presiona el botón A
        if (keys & 0x0001) {
            // Acción al presionar el botón A
        }

        // Verifica si se presiona el botón B
        if (keys & 0x0002) {
            // Acción al presionar el botón B
        }

        // Verifica si se presiona el botón derecho
        if (keys & 0x0010) {
            // Acción al presionar el botón derecho
        }

        // Verifica si se presiona el botón izquierdo
        if (keys & 0x0020) {
            // Acción al presionar el botón izquierdo
        }

        // Verifica si se presiona el botón arriba
        if (keys & 0x0040) {
            // Acción al presionar el botón arriba
        }

        // Verifica si se presiona el botón abajo
        if (keys & 0x0080) {
            // Acción al presionar el botón abajo
        }
    }

    return 0;
}