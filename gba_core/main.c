#include "kaia_gba.h"

// Definimos el tamaño de cada tile en el grid
#define TILE_SIZE 16

// Estructura para almacenar el estado de las teclas
typedef struct {
    unsigned short keys_held;
    unsigned short keys_pressed;
} InputState;

// Función para dibujar la grid en la pantalla
void dibujarGrid() {
    for (int i = 0; i < 240; i += TILE_SIZE) {
        // Dibujar línea horizontal
        for (int j = 0; j < 160; j++) {
            if (i == 0 || i == 240 - TILE_SIZE) {
                // Borde superior e inferior
                SetPixel(j, i, RGB(128, 128, 128));
            } else {
                // Líneas internas
                if (j == 0 || j == 160 - TILE_SIZE) {
                    // Borde izquierdo y derecho
                    SetPixel(j, i, RGB(128, 128, 128));
                }
            }
        }
    }
    for (int i = 0; i < 160; i += TILE_SIZE) {
        // Dibujar línea vertical
        for (int j = 0; j < 240; j++) {
            if (i == 0 || i == 160 - TILE_SIZE) {
                // Borde izquierdo y derecho
                SetPixel(i, j, RGB(128, 128, 128));
            } else {
                // Líneas internas
                if (j == 0 || j == 240 - TILE_SIZE) {
                    // Borde superior e inferior
                    SetPixel(i, j, RGB(128, 128, 128));
                }
            }
        }
    }
}

int main() {
    // Inicializar el estado de las teclas
    InputState input_state;
    input_state.keys_held = 0;
    input_state.keys_pressed = 0;

    // Inicializar las coordenadas iniciales como múltiplos de 16
    int x = 0;
    int y = 0;

    while (1) {
        // Leer el estado de las teclas
        input_state.keys_pressed = ~input_state.keys_held & (KEY_A | KEY_B | KEY_LEFT | KEY_RIGHT | KEY_UP | KEY_DOWN);
        input_state.keys_held = (KEY_A | KEY_B | KEY_LEFT | KEY_RIGHT | KEY_UP | KEY_DOWN);

        // Dibujar la grid
        dibujarGrid();

        // Manejar el movimiento discreto
        if (input_state.keys_pressed & KEY_LEFT) {
            x -= TILE_SIZE;
        }
        if (input_state.keys_pressed & KEY_RIGHT) {
            x += TILE_SIZE;
        }
        if (input_state.keys_pressed & KEY_UP) {
            y -= TILE_SIZE;
        }
        if (input_state.keys_pressed & KEY_DOWN) {
            y += TILE_SIZE;
        }

        // Asegurarse de que las coordenadas sean múltiplos de 16
        x = (x / TILE_SIZE) * TILE_SIZE;
        y = (y / TILE_SIZE) * TILE_SIZE;

        // Actualizar la pantalla
        vid_vsync();
    }

    return 0;
}