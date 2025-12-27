#include "kaia_gba.h"

int main() {
    // Limpieza inicial
    for(int i=0; i<38400; i++) VRAM[i] = NEGRO;
    int x = 80;
    int y = 60;
    while (1) {
        dibujarJugador(x, y, NEGRO); // Borrar viejo
        if (!(REG_KEYINPUT & KEY_RIGHT)) x++;
        if (!(REG_KEYINPUT & KEY_LEFT))  x--;
        if (!(REG_KEYINPUT & KEY_UP))    y--;
        if (!(REG_KEYINPUT & KEY_DOWN))  y++;
        dibujarJugador(x, y, AZUL);  // Pintar nuevo
        vid_vsync();
    }
    return 0;
}