#include "kaia_gba.h"

int main() {
    // Inicializar el modo de video
    REG_DISPCNT = 0x0400;

    while (1) {
        // Esperar a que se complete el ciclo de video
        vid_vsync();

        // Dibujar al jugador
        dibujarJugador();

        // Revisar las teclas presionadas
        if (REG_KEYCNT & KEY_RIGHT) {
            // Mover al jugador a la derecha
        }
    }

    return 0;
}