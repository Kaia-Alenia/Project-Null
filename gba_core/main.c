#include "kaia_gba.h"

// --- 1. COLORES ---
#define NEGRO    0x0000
#define AZUL     0x7C00
#define ROJO     0x001F
#define VERDE    0x03E0
#define AMARILLO 0x03FF

// --- 2. ESTRUCTURAS ---
typedef struct {
    int x, y;
    int w, h;
    u16 color;
} Entity;

// --- 3. VARIABLES GLOBALES ---
unsigned int seed = 12345;
int score = 0;

// --- 4. FUNCIONES DE MOTOR ---

// Generador Random Manual (LCG) porque no tenemos stdlib
int mi_random(int max) {
    seed = seed * 1103515245 + 12345;
    return (unsigned int)(seed / 65536) % max;
}

void vid_vsync() {
    while(REG_VCOUNT >= 160);
    while(REG_VCOUNT < 160);
}

// Dibuja o Borra. Si pasas color=0, usa el color de la entidad.
void dibujarEntidad(Entity *e, u16 color_override) {
    u16 color_final = (color_override == 0) ? e->color : color_override;
    
    for(int i = 0; i < e->w; i++) {
        for(int j = 0; j < e->h; j++) {
            int px = e->x + i;
            int py = e->y + j;
            // Safety Check
            if(px >= 0 && px < 240 && py >= 0 && py < 160) {
                VRAM[py * 240 + px] = color_final;
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

// --- 5. MAIN ---
int main() {
    REG_DISPCNT = MODE_3 | BG2_ENABLE;

    Entity jugador = {120, 80, 16, 16, AZUL};
    Entity moneda  = {50, 50, 8, 8, AMARILLO};

    // Limpieza inicial
    for(int i=0; i<38400; i++) VRAM[i] = NEGRO;

    while (1) {
        // A. Borrar rastro (Pintar NEGRO)
        dibujarEntidad(&jugador, NEGRO);
        dibujarEntidad(&moneda, NEGRO);

        // B. Input
        if (!(REG_KEYINPUT & KEY_RIGHT)) { if (jugador.x + jugador.w < 240) jugador.x++; }
        if (!(REG_KEYINPUT & KEY_LEFT))  { if (jugador.x > 0) jugador.x--; }
        if (!(REG_KEYINPUT & KEY_UP))    { if (jugador.y > 0) jugador.y--; }
        if (!(REG_KEYINPUT & KEY_DOWN))  { if (jugador.y + jugador.h < 160) jugador.y++; }

        // C. Lógica de Juego (Score y Colores)
        if (checarColision(&jugador, &moneda)) {
            score++; 
            
            // Cambiar color según nivel
            if (score >= 10) jugador.color = VERDE;
            else if (score >= 5)  jugador.color = ROJO;

            // Mover moneda
            moneda.x = mi_random(220);
            moneda.y = mi_random(140);
        }

        // D. Dibujar nuevos estados (0 = usar color del struct)
        dibujarEntidad(&moneda, 0);  
        dibujarEntidad(&jugador, 0); 

        // E. Sync
        vid_vsync();
    }
    return 0;
}