#include "kaia_gba.h"
#define NEGRO   0x0000
#define AZUL    0x7C00  // (31 << 10)

void vid_vsync() {
    while(REG_VCOUNT >= 160); // Esperar a que termine VBlank
    while(REG_VCOUNT < 160);  // Esperar a que empiece VBlank
}

void dibujarJugador(int x, int y, u16 color) {
    // Dibuja un cuadrado de 16x16
    for(int i = 0; i < 16; i++) {
        for(int j = 0; j < 16; j++) {
            // Escribe directamente en VRAM
            VRAM[(y + j) * 240 + (x + i)] = color;
        }
    }
}

int main() {
    // Configurar Pantalla
    REG_DISPCNT = MODE_3 | BG2_ENABLE;
    int posX = 120;
    int posY = 80;
    // Bucle Principal
    while (1) {
        // A. Borrar posición vieja (Pintar NEGRO)
        dibujarJugador(posX, posY, NEGRO);
        // B. Leer Inputs (Recuerda: 0 es presionado)
        if (!(REG_KEYINPUT & KEY_RIGHT)) posX++;
        if (!(REG_KEYINPUT & KEY_LEFT))  posX--;
        if (!(REG_KEYINPUT & KEY_UP))    posY--;
        if (!(REG_KEYINPUT & KEY_DOWN))  posY++;
        // C. Dibujar posición nueva (Pintar AZUL)
        dibujarJugador(posX, posY, AZUL);
        // D. Sincronizar
        vid_vsync();
    }
    return 0;
}