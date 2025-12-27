#include "kaia_gba.h"

// Función para sincronizar con la velocidad vertical
void vid_vsync() {
    while (REG_VCOUNT < 160);
}

// Función helper para dibujar un jugador
void dibujarJugador(int x, int y, u16 color) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            VRAM[(y + i) * 240 + x + j] = color;
        }
    }
}

int main() {
    // Inicializa modo de video
    REG_DISPCTL = MODE_3 | BG2_ENABLE;

    int x = 100;
    int y = 100;

    while (1) {
        // Paso A (Borrar)
        dibujarJugador(x, y, 0);

        // Paso B (Input)
        if (!(REG_KEYINPUT & KEY_RIGHT)) {
            x += 1;
            if (x > 235) {
                x = 0;
            }
        }

        // Paso C (Dibujar)
        dibujarJugador(x, y, 0x001F); // Azul

        // Paso D (Sincronizar)
        vid_vsync();
    }

    return 0;
}