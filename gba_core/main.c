#include "kaia_gba.h"

#define NEGRO 0x0000
#define AZUL 0x7C00
#define ROJO 0x001F
#define VERDE 0x03E0
#define AMARILLO 0x03FF

struct Entity {
    int x, y;
    int color;
};

int mi_random(int max) {
    return (rand() % max);
}

void vid_vsync() {
    while (REG_VCOUNT >= 160);
}

void dibujarEntidad(struct Entity e) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            setPixel(e.x + i, e.y + j, e.color);
        }
    }
}

int checarColision(struct Entity e1, struct Entity e2) {
    if (e1.x < e2.x + 10 && e1.x + 10 > e2.x && e1.y < e2.y + 10 && e1.y + 10 > e2.y) {
        return 1;
    }
    return 0;
}

int main() {
    struct Entity jugador;
    jugador.x = 10;
    jugador.y = 10;
    jugador.color = AZUL;

    struct Entity enemigo;
    enemigo.x = 50;
    enemigo.y = 50;
    enemigo.color = ROJO;

    int score = 0;

    while (1) {
        vid_vsync();
        dibujarEntidad(jugador);
        dibujarEntidad(enemigo);

        if (checarColision(jugador, enemigo)) {
            score++;
            jugador.color = (jugador.color == AZUL) ? VERDE : AZUL;
        }

        delay(100);
    }

    return 0;
}