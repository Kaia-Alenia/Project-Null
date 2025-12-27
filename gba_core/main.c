#include "kaia_gba.h"

// Estructura para el cuadrado
typedef struct {
    int x, y;
    int velocidadX, velocidadY;
} Cuadrado;

// Función para inicializar el cuadrado
void inicializarCuadrado(Cuadrado* cuadrado) {
    cuadrado->x = 10;
    cuadrado->y = 10;
    cuadrado->velocidadX = 1;
    cuadrado->velocidadY = 1;
}

// Función para actualizar el cuadrado
void actualizarCuadrado(Cuadrado* cuadrado) {
    cuadrado->x += cuadrado->velocidadX;
    cuadrado->y += cuadrado->velocidadY;

    // Rebotar en los bordes
    if (cuadrado->x < 0 || cuadrado->x > 230) {
        cuadrado->velocidadX = -cuadrado->velocidadX;
    }
    if (cuadrado->y < 0 || cuadrado->y > 150) {
        cuadrado->velocidadY = -cuadrado->velocidadY;
    }
}

// Función para dibujar el cuadrado
void dibujarCuadrado(Cuadrado* cuadrado) {
    // Dibujar el cuadrado en la pantalla
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (cuadrado->x + i < 240 && cuadrado->y + j < 160) {
                ((unsigned short*)(0x06000000 + (cuadrado->y + j) * 240 + (cuadrado->x + i))) = 0x7FFF;
            }
        }
    }
}

// Función para sincronización vertical
void vid_vsync() {
    while (REG_VCOUNT < 160);
}

int main() {
    // Inicializar el cuadrado
    Cuadrado cuadrado;
    inicializarCuadrado(&cuadrado);

    // Configurar el modo de video
    REG_DISPCTL = MODE_3 | BG2_ENABLE;

    while (1) {
        // Borrar la pantalla
        for (int i = 0; i < 160; i++) {
            for (int j = 0; j < 240; j++) {
                ((unsigned short*)(0x06000000 + i * 240 + j)) = 0;
            }
        }

        // Actualizar el cuadrado
        actualizarCuadrado(&cuadrado);

        // Dibujar el cuadrado
        dibujarCuadrado(&cuadrado);

        // Sincronización vertical
        vid_vsync();
    }

    return 0;
}