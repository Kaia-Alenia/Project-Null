```c
#include "kaia_gba.h"

// --- CONSTANTES ---
#define NEGRO 0x0000
#define AZUL 0x7C00
#define AMARILLO 0x03FF

// --- ESTRUCTURAS ---
typedef struct {
    int x, y;
    int w, h;
    u16 color;
} Entity;

// --- VARIABLES GLOBALES (Para Random simple) ---
unsigned int seed = 12345;

// --- FUNCIONES ---

// Generador de números pseudo-aleatorios (LCG simple)
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

// Detectar colisión AABB (Cajas alineadas a los ejes)
int checarColision(Entity *a, Entity *b) {
    return !(a->x + a->w <= b->x ||  // A está a la izquierda de B
             a->x >= b->x + b->w ||  // A está a la derecha de B
             a->y + a->h <= b->y ||  // A está arriba de B
             a->y >= b->y + b->h);   // A está abajo de B
}

// --- MAIN ---
int main() {
    REG_DISPCNT = MODE_3 | BG2_ENABLE;

    // Inicializar Entidades
    Entity jugador = {120, 80, 16, 16, AZUL};
    Entity moneda  = {50, 50, 8, 8, AMARILLO}; // Moneda más pequeña (8x8)

    // Limpieza inicial
    for(int i=0; i<38400; i++) VRAM[i] = NEGRO;

    while (1) {
        // 1. BORRAR (Pintar NEGRO)
        dibujarEntidad(&jugador, NEGRO);
        dibujarEntidad(&moneda, NEGRO);

        // 2. INPUT Y FÍSICA
        if (!(REG_KEYINPUT & KEY_RIGHT)) { if (jugador.x + jugador.w < 240) jugador.x++; }
        if (!(REG_KEYINPUT & KEY_LEFT))  { if (jugador.x > 0) jugador.x--; }
        if (!(REG_KEYINPUT & KEY_UP))    { if (jugador.y > 0) jugador.y--; }
        if (!(REG_KEYINPUT & KEY_DOWN))  { if (jugador.y + jugador.h < 160) jugador.y++; }

        // 3. LÓGICA DE JUEGO (Colisión)
        if (checarColision(&jugador, &moneda)) {
            // Si toca la moneda, moverla a un lugar aleatorio
            // (Borramos la moneda vieja antes de moverla para no dejar rastro)
            dibujarEntidad(&moneda, NEGRO); 

            // Asegurarse de que la moneda no se salga de la pantalla
            moneda.x = mi_random(232 - moneda.w); // Rango seguro X
            moneda.y = mi_random(152 - moneda.h); // Rango seguro Y
        }

        // 4. DIBUJAR (Pintar color real)
        dibujarEntidad(&moneda, moneda.color);
        dibujarEntidad(&jugador, jugador.color);

        // 5. SYNC
        vid_vsync();
    }

    return 0;
}
```