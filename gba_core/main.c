#include "kaia_gba.h"

// --- CONFIGURACIÓN ---
#define TILE_SIZE 16

// Colores 15-bit
#define NEGRO    0x0000
#define GRIS     0x3186
#define AZUL     0x7C00
#define ROJO     0x001F
#define VERDE    0x03E0
#define AMARILLO 0x03FF

typedef struct { int x, y; u16 color; } Entity;

unsigned int seed = 12345;
int score = 0;

int mi_random(int max) {
    seed = seed * 1103515245 + 12345;
    return (unsigned int)(seed / 65536) % max;
}

int snap(int val) { return (val / TILE_SIZE) * TILE_SIZE; }

void vid_vsync() {
    while(REG_VCOUNT >= 160);
    while(REG_VCOUNT < 160);
}

void dibujarJugador(int x, int y, u16 color) {
    for(int i = 1; i < TILE_SIZE-1; i++) { 
        for(int j = 1; j < TILE_SIZE-1; j++) {
            int px = x + i;
            int py = y + j;
            if(px >= 0 && px < 240 && py >= 0 && py < 160) {
                VRAM[py * 240 + px] = color;
            }
        }
    }
}

void dibujarGridCompleto() {
    for(int i=0; i<38400; i++) VRAM[i] = NEGRO;
    for(int x=0; x<240; x+=TILE_SIZE) 
        for(int y=0; y<160; y++) VRAM[y*240+x] = GRIS;
    for(int y=0; y<160; y+=TILE_SIZE) 
        for(int x=0; x<240; x++) VRAM[y*240+x] = GRIS;
}

void restaurarCasilla(int x, int y) {
    for(int i = 0; i < TILE_SIZE; i++) {
        for(int j = 0; j < TILE_SIZE; j++) {
            int px = x + i;
            int py = y + j;
            if (px >= 0 && px < 240 && py >= 0 && py < 160) {
                u16 color = (i == 0 || j == 0) ? GRIS : NEGRO;
                VRAM[py * 240 + px] = color;
            }
        }
    }
}

int main() {
    REG_DISPCNT = MODE_3 | BG2_ENABLE;

    // AQUI EL CAMBIO QUE ELLA DEBIO HACER (VERDE)
    Entity jugador = {snap(120), snap(80), VERDE};
    Entity moneda  = {snap(48), snap(48), AMARILLO};

    dibujarGridCompleto();
    dibujarJugador(jugador.x, jugador.y, jugador.color);
    dibujarJugador(moneda.x, moneda.y, moneda.color);

    u16 keys_ant = 0;

    while (1) {
        vid_vsync();
        u16 keys = REG_KEYINPUT;
        u16 down = (keys_ant ^ keys) & ~keys;
        keys_ant = keys;

        int dx = 0, dy = 0;
        if (down & KEY_RIGHT) dx = TILE_SIZE;
        if (down & KEY_LEFT)  dx = -TILE_SIZE;
        if (down & KEY_UP)    dy = -TILE_SIZE;
        if (down & KEY_DOWN)  dy = TILE_SIZE;

        if (dx != 0 || dy != 0) {
            int nx = jugador.x + dx;
            int ny = jugador.y + dy;
            if (nx >= 0 && nx < 240 && ny >= 0 && ny < 160) {
                restaurarCasilla(jugador.x, jugador.y);
                jugador.x = nx;
                jugador.y = ny;
                dibujarJugador(jugador.x, jugador.y, jugador.color);
            }
        }

        if (jugador.x == moneda.x && jugador.y == moneda.y) {
            score++;
            if(score >= 5) jugador.color = ROJO;
            restaurarCasilla(moneda.x, moneda.y); 
            moneda.x = snap(mi_random(220));
            moneda.y = snap(mi_random(140));
            dibujarJugador(moneda.x, moneda.y, moneda.color);
            dibujarJugador(jugador.x, jugador.y, jugador.color);
        }
    }
    return 0;
}
