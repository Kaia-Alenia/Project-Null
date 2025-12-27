#include "kaia_gba.h"

// --- 1. CONFIGURACIÓN TÁCTICA ---
#define TILE_SIZE 16  // Tamaño de la casilla (Grid)
#define SPRITE_SIZE 14 // Tamaño del personaje (para no tocar la rejilla)
#define OFFSET 1       // Margen para centrar el personaje en la casilla

// Colores 15-bit (0xBBGGRR)
#define NEGRO    0x0000
#define GRIS     0x3186  // Color de la rejilla
#define AZUL     0x7C00
#define ROJO     0x001F
#define VERDE    0x03E0
#define AMARILLO 0x03FF

// --- 2. ESTRUCTURAS ---
typedef struct {
    int x, y; // Posición base (esquina superior izquierda de la casilla)
    u16 color;
} Entity;

// --- 3. VARIABLES GLOBALES ---
unsigned int seed = 12345;
int score = 0;

// --- 4. FUNCIONES DE MOTOR ---

// Generador Random LCG
int mi_random(int max) {
    seed = seed * 1103515245 + 12345;
    return (unsigned int)(seed / 65536) % max;
}

// Alinea una coordenada a la rejilla (snap to grid)
int snap(int val) {
    return (val / TILE_SIZE) * TILE_SIZE;
}

void vid_vsync() {
    while(REG_VCOUNT >= 160);
    while(REG_VCOUNT < 160);
}

// Dibuja un rectángulo sólido. Se usa para pintar personajes y para borrarlos.
void dibujarRect(int x, int y, int w, int h, u16 color) {
    for(int i = 0; i < w; i++) {
        for(int j = 0; j < h; j++) {
            int px = x + i;
            int py = y + j;
            // Safety Check: CRÍTICO para evitar corrupción de VRAM
            if(px >= 0 && px < 240 && py >= 0 && py < 160) {
                VRAM[py * 240 + px] = color;
            }
        }
    }
}

// Dibuja la rejilla completa. ESTA FUNCIÓN ES LENTA Y SOLO SE LLAMA UNA VEZ.
void dibujarGrid() {
    // 1. Fondo Negro
    for(int i=0; i<38400; i++) VRAM[i] = NEGRO;
    
    // 2. Líneas Verticales
    for(int x = 0; x < 240; x += TILE_SIZE) {
        for(int y = 0; y < 160; y++) VRAM[y*240 + x] = GRIS;
    }
    // 3. Líneas Horizontales
    for(int y = 0; y < 160; y += TILE_SIZE) {
        for(int x = 0; x < 240; x++) VRAM[y*240 + x] = GRIS;
    }
}

int checarColision(Entity *a, Entity *b) {
    // En un grid, la colisión es exacta si comparten la misma casilla base.
    return (a->x == b->x && a->y == b->y);
}

// --- 5. MAIN (Bucle de Juego) ---
int main() {
    REG_DISPCNT = MODE_3 | BG2_ENABLE;

    // A. DIBUJAR GRID ESTÁTICO (OPTIMIZACIÓN CLAVE)
    // Se llama FUERA del bucle. Nunca más se redibuja.
    dibujarGrid();

    // Inicialización de entidades alineadas a la rejilla
    Entity jugador = {snap(120), snap(80), AZUL};
    Entity moneda  = {snap(48), snap(48), AMARILLO};

    u16 keys_actuales = 0;
    u16 keys_anteriores = 0;

    while (1) {
        // B. INPUT (Detección de Flancos para movimiento paso a paso)
        keys_actuales = REG_KEYINPUT;
        // keys_down será 1 solo en el frame exacto en que se presiona un botón
        u16 keys_down = (keys_anteriores ^ keys_actuales) & ~keys_actuales;

        // C. BORRAR POSICIÓN VIEJA
        // Usamos el OFFSET (+1) y el tamaño reducido (14x14).
        // Al pintar de NEGRO, solo borramos el interior de la celda. ¡La rejilla gris queda intacta!
        dibujarRect(jugador.x + OFFSET, jugador.y + OFFSET, SPRITE_SIZE, SPRITE_SIZE, NEGRO);

        // D. LÓGICA DE MOVIMIENTO
        // Solo nos movemos si se detectó una nueva pulsación (keys_down)
        if (keys_down & KEY_RIGHT) { if (jugador.x + TILE_SIZE < 240) jugador.x += TILE_SIZE; }
        if (keys_down & KEY_LEFT)  { if (jugador.x > 0)               jugador.x -= TILE_SIZE; }
        if (keys_down & KEY_UP)    { if (jugador.y > 0)               jugador.y -= TILE_SIZE; }
        if (keys_down & KEY_DOWN)  { if (jugador.y + TILE_SIZE < 160) jugador.y += TILE_SIZE; }

        keys_anteriores = keys_actuales;

        // E. LÓGICA DE JUEGO (Colisión y Estado)
        if (checarColision(&jugador, &moneda)) {
            score++;
            if (score >= 5) jugador.color = ROJO;
            if (score >= 10) jugador.color = VERDE;

            // Borrar moneda vieja (con offset) antes de moverla
            dibujarRect(moneda.x + OFFSET, moneda.y + OFFSET, SPRITE_SIZE, SPRITE_SIZE, NEGRO);
            
            moneda.x = snap(mi_random(220));
            moneda.y = snap(mi_random(140));
        }

        // F. DIBUJAR NUEVA POSICIÓN
        // Dibujamos con el mismo OFFSET y tamaño que usamos para borrar.
        dibujarRect(moneda.x + OFFSET, moneda.y + OFFSET, SPRITE_SIZE, SPRITE_SIZE, moneda.color);
        dibujarRect(jugador.x + OFFSET, jugador.y + OFFSET, SPRITE_SIZE, SPRITE_SIZE, jugador.color);

        // G. SYNC
        vid_vsync();
    }
    return 0;
}
