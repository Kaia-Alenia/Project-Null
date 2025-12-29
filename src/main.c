#include <stdint.h>

// Definiciones de constantes para el juego de Tetris
#define SCREEN_W 240
#define SCREEN_H 160
#define BLOCK_SIZE 10
#define GRID_W 10
#define GRID_H 20

// Estructura para representar una pieza de Tetris
typedef struct {
    uint8_t x, y;
    uint8_t forma[4][2];
} Pieza;

// Función para inicializar una pieza de Tetris
void inicializar_pieza(Pieza* pieza) {
    // Inicializar la forma de la pieza (por ejemplo, una I)
    pieza->forma[0][0] = 0;
    pieza->forma[0][1] = 0;
    pieza->forma[1][0] = 1;
    pieza->forma[1][1] = 0;
    pieza->forma[2][0] = 2;
    pieza->forma[2][1] = 0;
    pieza->forma[3][0] = 3;
    pieza->forma[3][1] = 0;
    pieza->x = GRID_W / 2;
    pieza->y = 0;
}

// Función para dibujar una pieza de Tetris en la pantalla
void dibujar_pieza(Pieza* pieza) {
    for (int i = 0; i < 4; i++) {
        uint16_t* vram = (uint16_t*)0x06000000;
        vram[(pieza->y + pieza->forma[i][1]) * SCREEN_W / 2 + (pieza->x + pieza->forma[i][0])] = 0x001F; // Color blanco
    }
}

// Función para borrar una pieza de Tetris de la pantalla
void borrar_pieza(Pieza* pieza) {
    for (int i = 0; i < 4; i++) {
        uint16_t* vram = (uint16_t*)0x06000000;
        vram[(pieza->y + pieza->forma[i][1]) * SCREEN_W / 2 + (pieza->x + pieza->forma[i][0])] = 0x0000; // Color negro
    }
}

int main() {
    // Inicialización de la Game Boy Advance
    *(volatile uint16_t*)0x04000000 = 0x0400 | 0x0003; // Modo 3 y fondo 2 habilitado

    // Inicializar la pieza de Tetris
    Pieza pieza;
    inicializar_pieza(&pieza);

    while (1) {
        // Bucle principal del juego

        // Dibujar la pieza de Tetris
        dibujar_pieza(&pieza);

        // Esperar un poco para controlar la velocidad del juego
        for (int i = 0; i < 10000; i++) {
            // Nada
        }

        // Borrar la pieza de Tetris
        borrar_pieza(&pieza);

        // Mover la pieza de Tetris hacia abajo
        pieza.y++;

        // Comprobar si la pieza ha llegado al final de la pantalla
        if (pieza.y > GRID_H - 1) {
            // Reiniciar la pieza
            inicializar_pieza(&pieza);
        }
    }

    return 0;
}