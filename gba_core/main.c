#include "kaia_gba.h"

// --- CONSTANTES ---
#define NEGRO    0x0000
#define AZUL     0x7C00
#define AMARILLO 0x03FF

// --- ESTRUCTURAS ---
typedef struct {
    int x, y;
    int w, h;
    u16 color;
} Entity;

// --- VARIABLES GLOBALES ---
unsigned int seed = 12345;

// --- FUNCIONES ---

int mi_random(int max) {
    seed = seed * 1103515245 + 12345;
    return (unsigned int)(seed / 65536) % max;
}

void vid_vsync() {
    while(REG_VCOUNT >= 160);
    while(REG_VCOUNT < 160);
}

void dibujarEntidad(Entity *e, u16 color) {
    for(int i = 0; i < e->w; i++) {
        for(int j = 0; j < e->h; j++) {
            int px = e->x + i;
            int py = e->y + j;
            if(px >= 0 && px < 240 && py >= 0 && py < 160) {
                VRAM[py * 240 + px] = color;
            }
        }
    }
}

int checarColision(Entity *a, Entity *b) {
    return !(a->x + a->w <= b->x ||
             a->x >= b->x + b->w ||
             a->y + a->h <= b->y ||
             a->y >= b->y + b->h);
}

// --- MAIN ---
int main() {
    REG_DISPCNT = MODE_3 | BG2_ENABLE;

    Entity jugador = {120, 80, 16, 16, AZUL};
    Entity moneda  = {50, 50, 8, 8, AMARILLO};

    // Limpieza inicial
    for(int i=0; i<38400; i++) VRAM[i] = NEGRO;

    while (1) {
        // 1. BORRAR
        dibujarEntidad(&jugador, NEGRO);
        dibujarEntidad(&moneda, NEGRO);

        // 2. INPUT
        if (!(REG_KEYINPUT & KEY_RIGHT)) { if (jugador.x + jugador.w < 240) jugador.x++; }
        if (!(REG_KEYINPUT & KEY_LEFT))  { if (jugador.x > 0) jugador.x--; }
        if (!(REG_KEYINPUT & KEY_UP))    { if (jugador.y > 0) jugador.y--; }
        if (!(REG_KEYINPUT & KEY_DOWN))  { if (jugador.y + jugador.h < 160) jugador.y++; }

        // 3. COLISIÓN
        if (checarColision(&jugador, &moneda)) {
            dibujarEntidad(&moneda, NEGRO); // Borrar de pos vieja
            moneda.x = mi_random(220);
            moneda.y = mi_random(140);
        }

        // 4. DIBUJAR
        dibujarEntidad(&moneda, moneda.color);
        dibujarEntidad(&jugador, jugador.color);

        // 5. SYNC
        vid_vsync();
    }
    return 0;
}