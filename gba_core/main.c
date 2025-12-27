#include "kaia_gba.h"

// --- 1. DEFINICIONES ---
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

// --- 4. FUNCIONES ---

// Generador Random simple
int mi_random(int max) {
    seed = seed * 1103515245 + 12345;
    return (unsigned int)(seed / 65536) % max;
}

void vid_vsync() {
    while(REG_VCOUNT >= 160);
    while(REG_VCOUNT < 160);
}

// CORRECCIÓN CRÍTICA: Eliminada la lógica "if color == 0". 
// Ahora esta función pinta EXACTAMENTE lo que le digas.
void dibujarEntidad(Entity *e, u16 color) {
    for(int i = 0; i < e->w; i++) {
        for(int j = 0; j < e->h; j++) {
            int px = e->x + i;
            int py = e->y + j;
            
            // Safety Check: No salir de pantalla
            if(px >= 0 && px < 240 && py >= 0 && py < 160) {
                VRAM[py * 240 + px] = color;
            }
        }
    }
}

int checarColision(Entity *a, Entity *b) {
    // Retorna 1 si hay superposición, 0 si no
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

    // Limpieza inicial de toda la pantalla
    for(int i=0; i<38400; i++) VRAM[i] = NEGRO;

    while (1) {
        // A. BORRAR RASTRO
        // Pasamos NEGRO explícitamente. Ahora SÍ pintará negro.
        dibujarEntidad(&jugador, NEGRO);
        dibujarEntidad(&moneda, NEGRO);

        // B. INPUT Y FÍSICA
        if (!(REG_KEYINPUT & KEY_RIGHT)) { if (jugador.x + jugador.w < 240) jugador.x++; }
        if (!(REG_KEYINPUT & KEY_LEFT))  { if (jugador.x > 0) jugador.x--; }
        if (!(REG_KEYINPUT & KEY_UP))    { if (jugador.y > 0) jugador.y--; }
        if (!(REG_KEYINPUT & KEY_DOWN))  { if (jugador.y + jugador.h < 160) jugador.y++; }

        // C. LÓGICA DE JUEGO
        if (checarColision(&jugador, &moneda)) {
            score++; 
            
            // Feedback Visual de nivel
            if (score >= 10) jugador.color = VERDE;
            else if (score >= 5)  jugador.color = ROJO;

            // Mover moneda (El borrado ya ocurrió en el paso A)
            moneda.x = mi_random(220); // 240 - ancho aprox
            moneda.y = mi_random(140); // 160 - alto aprox
        }

        // D. DIBUJAR NUEVO ESTADO
        // Pasamos el color de la entidad explícitamente.
        dibujarEntidad(&moneda, moneda.color);  
        dibujarEntidad(&jugador, jugador.color); 

        // E. SYNC
        vid_vsync();
    }
    return 0;
}