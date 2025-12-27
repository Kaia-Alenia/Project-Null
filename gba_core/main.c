#include "kaia_gba.h"
// Colores
#define NEGRO 0x0000
#define AZUL  0x7C00
// -- Funciones --
void vid_vsync() {
    while(REG_VCOUNT >= 160); // Esperar si estamos en VBlank
    while(REG_VCOUNT < 160);  // Esperar a que empiece VBlank
}
void dibujarJugador(int x, int y, int color) {
    for(int i = 0; i < 16; i++) {
        for(int j = 0; j < 16; j++) {
            VRAM[(y + j) * 240 + (x + i)] = color;
        }
    }
}
int main() {
    REG_DISPCNT = MODE_3 | BG2_ENABLE;
    int x = 120;
    int y = 80;
    // Limpieza inicial
    for(int i=0; i<38400; i++) VRAM[i] = NEGRO;
    while (1) {
        // 1. Borrar (Pintar Negro en posición vieja)
        dibujarJugador(x, y, NEGRO);
        // 2. Input
        if (!(REG_KEYINPUT & KEY_RIGHT)) x++;
        if (!(REG_KEYINPUT & KEY_LEFT))  x--;
        if (!(REG_KEYINPUT & KEY_UP))    y--;
        if (!(REG_KEYINPUT & KEY_DOWN))  y++;
        // 3. Dibujar (Pintar Azul en posición nueva)
        dibujarJugador(x, y, AZUL);
        // 4. Sincronizar
        vid_vsync();
    }
    return 0;
}