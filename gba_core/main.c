#include <gba.h>

void vid_vsync() {
    while (REG_VCOUNT >= 160); // Espera a que la pantalla termine de dibujar
    while (REG_VCOUNT < 160); // Espera a que la pantalla comience a dibujar nuevamente
}

int main() {
    // Inicialización del juego
    // ...

    while (1) {
        // Bucle principal del juego
        // ...

        vid_vsync(); // Llamada a la función de sincronización vertical
    }

    return 0;
}