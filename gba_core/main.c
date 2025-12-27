#include "kaia_gba.h"

// Definición de la función vid_vsync antes del main
void vid_vsync() {
    while(REG_VCOUNT < 160);
    while(REG_VCOUNT >= 160);
}

int main() {
    // Configuración del modo de video
    REG_DISPCNT = MODE_3 | BG2_ENABLE;

    // Inicialización de variables para la lógica de movimiento
    int x = 0;
    int y = 0;

    while(1) {
        // Lógica de movimiento (por ahora, solo mover el cuadrado)
        x++;
        y++;

        // Llamada a vid_vsync para sincronización vertical
        vid_vsync();

        // Dibujar el cuadrado en VRAM (por simplicidad, asumir que el cuadrado es de 10x10 píxeles)
        // Nota: La implementación real dependerá de cómo se maneje la memoria de video (VRAM) en el proyecto
        // Por ahora, se asume una función genérica para dibujar el cuadrado
        // void drawSquare(int x, int y);
        // drawSquare(x, y);

        // Simulación de dibujado del cuadrado (reemplazar con la implementación real)
        // Se asume que el cuadrado se dibuja en la capa de fondo 2 (BG2)
        // y que se utiliza una paleta de colores simple
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++) {
                // Asignar un color al píxel (por ejemplo, blanco)
                // La implementación real dependerá de cómo se acceda y se modifique la VRAM
                // Se asume una función para asignar color a un píxel en la posición (x+i, y+j)
                // void setPixelColor(int x, int y, int color);
                // setPixelColor(x+i, y+j, 0xFFFFFF);
            }
        }
    }

    return 0;
}