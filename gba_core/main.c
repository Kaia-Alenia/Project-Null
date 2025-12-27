#include <gba.h>

int main() {
    // Inicialización del hardware
    REG_DISPCNT = MODE_0 | BG2_ENABLE;

    while (1) {
        // Bucle principal del juego
        // ...

        // Aplicación de VSync para evitar parpadeo
        while (REG_VCOUNT >= 160);
        // ...

        // Actualización de la pantalla
        // ...
    }

    return 0;
}