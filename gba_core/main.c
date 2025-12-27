#include "kaia_gba.h"

typedef struct {
    int x, y;
    int w, h; // Ancho y alto (16x16)
    u16 color;
} Player;

void dibujarJugador(Player *p, u16 color) {
    // Dibujar jugador en la posición x, y con el ancho y alto definidos
    // y el color especificado
    for (int i = 0; i < p->h; i++) {
        for (int j = 0; j < p->w; j++) {
            setPixel(p->x + j, p->y + i, color);
        }
    }
}

int main() {
    Player p = {120, 80, 16, 16, AZUL};
    u16 color = AZUL;

    while (1) {
        // Lógica de input
        if (keysDown() & KEY_LEFT) {
            if (p.x > 0) {
                p.x--;
            }
        }
        if (keysDown() & KEY_RIGHT) {
            if (p.x < 240 - p.w) {
                p.x++;
            }
        }
        if (keysDown() & KEY_UP) {
            if (p.y > 0) {
                p.y--;
            }
        }
        if (keysDown() & KEY_DOWN) {
            if (p.y < 160 - p.h) {
                p.y++;
            }
        }

        // Dibujar jugador
        dibujarJugador(&p, p.color);

        // Actualizar pantalla
        vid_vsync();
    }

    return 0;
}