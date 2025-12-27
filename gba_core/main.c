#include "kaia_gba.h"

// Definición del cuadrado
#define CUADRADO_TAMANIO 10

// Variables para la posición del cuadrado
int posX = 100;
int posY = 100;

int main() {
    // Inicio: Limpia la pantalla completa a NEGRO una sola vez
    for (int y = 0; y < 160; y++) {
        for (int x = 0; x < 240; x++) {
            plotPixel(x, y, 0); // 0 es el color negro
        }
    }

    while (1) {
        // Paso A (Borrar Rastro): Dibuja el cuadrado de color NEGRO en la posición actual
        for (int y = 0; y < CUADRADO_TAMANIO; y++) {
            for (int x = 0; x < CUADRADO_TAMANIO; x++) {
                if (posX + x >= 0 && posX + x < 240 && posY + y >= 0 && posY + y < 160) {
                    plotPixel(posX + x, posY + y, 0); // 0 es el color negro
                }
            }
        }

        // Paso B (Lógica): Lee los inputs y actualiza posX / posY
        // Aquí debes agregar la lógica para leer los inputs y actualizar las variables posX y posY
        // Por ejemplo, si se presiona la tecla derecha, aumentar posX
        if (keysDown() & KEY_RIGHT) {
            posX += 1;
        }
        if (keysDown() & KEY_LEFT) {
            posX -= 1;
        }
        if (keysDown() & KEY_UP) {
            posY -= 1;
        }
        if (keysDown() & KEY_DOWN) {
            posY += 1;
        }

        // Paso C (Dibujar Nuevo): Dibuja el cuadrado de color AZUL en la nueva posición
        for (int y = 0; y < CUADRADO_TAMANIO; y++) {
            for (int x = 0; x < CUADRADO_TAMANIO; x++) {
                if (posX + x >= 0 && posX + x < 240 && posY + y >= 0 && posY + y < 160) {
                    plotPixel(posX + x, posY + y, 31); // 31 es el color azul
                }
            }
        }

        // Paso D (VSync): Llama a vid_vsync()
        vid_vsync();
    }

    return 0;
}