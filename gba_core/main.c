#include "kaia_gba.h"

// Definiciones de colores
#define GRIS 0xCCCCCC
#define NEGRO 0x000000

// Definiciones de tamaños
#define CASILLA_TAM 16
#define JUGADOR_TAM 14

// Variables globales
u16* videoBuffer = (u16*) 0x06000000;
u16 keys_down;

// Función para dibujar la rejilla
void dibujarGrid() {
    for (int y = 0; y < 160; y += CASILLA_TAM) {
        for (int x = 0; x < 240; x += CASILLA_TAM) {
            // Dibujar borde gris
            for (int i = 0; i < CASILLA_TAM; i++) {
                videoBuffer[(y * 240) + x + i] = GRIS;
                videoBuffer[((y + CASILLA_TAM - 1) * 240) + x + i] = GRIS;
            }
            for (int i = 0; i < CASILLA_TAM; i++) {
                videoBuffer[(y + i) * 240 + x] = GRIS;
                videoBuffer[(y + i) * 240 + x + CASILLA_TAM - 1] = GRIS;
            }
        }
    }
}

// Función para dibujar al jugador
void dibujarJugador(int x, int y) {
    for (int i = 0; i < JUGADOR_TAM; i++) {
        for (int j = 0; j < JUGADOR_TAM; j++) {
            videoBuffer[((y + 1 + i) * 240) + x + 1 + j] = 0xFFFFFF; // Color del jugador
        }
    }
}

// Función para borrar al jugador
void borrarJugador(int x, int y) {
    for (int i = 0; i < JUGADOR_TAM; i++) {
        for (int j = 0; j < JUGADOR_TAM; j++) {
            videoBuffer[((y + 1 + i) * 240) + x + 1 + j] = NEGRO;
        }
    }
}

int main() {
    // Inicializar la rejilla
    dibujarGrid();

    int jugadorX = 0;
    int jugadorY = 0;

    while (1) {
        // Leer entradas
        keys_down = ~REG_KEY_INPUT;

        // Mover al jugador
        if (keys_down & KEY_LEFT) {
            borrarJugador(jugadorX, jugadorY);
            jugadorX -= CASILLA_TAM;
            dibujarJugador(jugadorX, jugadorY);
        }
        if (keys_down & KEY_RIGHT) {
            borrarJugador(jugadorX, jugadorY);
            jugadorX += CASILLA_TAM;
            dibujarJugador(jugadorX, jugadorY);
        }
        if (keys_down & KEY_UP) {
            borrarJugador(jugadorX, jugadorY);
            jugadorY -= CASILLA_TAM;
            dibujarJugador(jugadorX, jugadorY);
        }
        if (keys_down & KEY_DOWN) {
            borrarJugador(jugadorX, jugadorY);
            jugadorY += CASILLA_TAM;
            dibujarJugador(jugadorX, jugadorY);
        }

        // Esperar a la siguiente VBlank
        vid_vsync();
    }

    return 0;
}