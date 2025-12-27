#include "kaia_gba.h"

// --- CONFIGURACIÓN ---
#define TILE_SIZE 16

// Colores 15-bit (0xBBGGRR)
#define NEGRO    0x0000
#define GRIS     0x3186
#define AZUL     0x7C00
#define ROJO     0x001F
#define VERDE    0x03E0
#define AMARILLO 0x03FF

// --- ESTRUCTURAS ---
typedef struct { 
    int x, y; 
    u16 color; 
} Entity;

typedef struct {
    int x, y;
    u16 color;
    int timer;     // Para controlar velocidad
    int direccion; // 0-3
} Enemy;

// --- VARIABLES GLOBALES ---
unsigned int seed = 12345;
int score = 0;

// --- FUNCIONES ---

int mi_random(int max) {
    seed = seed * 1103515245 + 12345;
    return (unsigned int)(seed / 65536) % max;
}

int snap(int val) { return (val / TILE_SIZE) * TILE_SIZE; }

void vid_vsync() {
    while(REG_VCOUNT >= 160);
    while(REG_VCOUNT < 160);
}

// Dibuja entidad (Jugador/Enemigo/Moneda) con margen
void dibujarEntidad(int x, int y, u16 color) {
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

// Dibuja la rejilla inicial
void dibujarGridCompleto() {
    for(int i=0; i<38400; i++) VRAM[i] = NEGRO;
    for(int x=0; x<240; x+=TILE_SIZE) 
        for(int y=0; y<160; y++) VRAM[y*240+x] = GRIS;
    for(int y=0; y<160; y+=TILE_SIZE) 
        for(int x=0; x<240; x++) VRAM[y*240+x] = GRIS;
}

// RESTAURACIÓN ACTIVA: Borra contenido y repara bordes grises
void restaurarCasilla(int x, int y) {
    for(int i = 0; i < TILE_SIZE; i++) {
        for(int j = 0; j < TILE_SIZE; j++) {
            int px = x + i;
            int py = y + j;
            if (px >= 0 && px < 240 && py >= 0 && py < 160) {
                // Si es borde, pinta GRIS. Si es centro, pinta NEGRO.
                u16 color = (i == 0 || j == 0) ? GRIS : NEGRO;
                VRAM[py * 240 + px] = color;
            }
        }
    }
}

// --- MAIN ---
int main() {
    REG_DISPCNT = MODE_3 | BG2_ENABLE;

    // Inicialización
    Entity jugador = {snap(120), snap(80), VERDE}; // Jugador VERDE como pediste
    Entity moneda  = {snap(48), snap(48), AMARILLO};
    
    // Enemigo ROJO en esquina inferior derecha
    Enemy enemigo = {snap(224), snap(144), ROJO, 0, 0};

    dibujarGridCompleto();
    dibujarEntidad(jugador.x, jugador.y, jugador.color);
    dibujarEntidad(moneda.x, moneda.y, moneda.color);
    dibujarEntidad(enemigo.x, enemigo.y, enemigo.color);

    u16 keys_ant = 0;

    while (1) {
        vid_vsync();
        
        // INPUT CORREGIDO: Usamos XOR para detectar flancos (pulsación nueva)
        u16 keys = REG_KEYINPUT;
        u16 down = (keys_ant ^ keys) & ~keys; 
        keys_ant = keys;

        // --- 1. LÓGICA JUGADOR ---
        int dx = 0, dy = 0;
        if (down & KEY_RIGHT) dx = TILE_SIZE;
        if (down & KEY_LEFT)  dx = -TILE_SIZE;
        if (down & KEY_UP)    dy = -TILE_SIZE;
        if (down & KEY_DOWN)  dy = TILE_SIZE;

        if (dx != 0 || dy != 0) {
            int nx = jugador.x + dx;
            int ny = jugador.y + dy;
            
            if (nx >= 0 && nx < 240 && ny >= 0 && ny < 160) {
                restaurarCasilla(jugador.x, jugador.y); // Borrar rastro viejo
                jugador.x = nx;
                jugador.y = ny;
                dibujarEntidad(jugador.x, jugador.y, jugador.color); // Pintar nuevo
            }
        }

        // --- 2. LÓGICA ENEMIGO (IA Simple) ---
        enemigo.timer++;
        if (enemigo.timer > 30) { // Mover cada 30 frames (aprox 0.5 seg)
            enemigo.timer = 0;
            
            // Borrar posición vieja ANTES de calcular la nueva
            restaurarCasilla(enemigo.x, enemigo.y);

            // Elegir dirección aleatoria
            int r = mi_random(4);
            int ex = 0, ey = 0;
            if (r==0) ex = TILE_SIZE;
            if (r==1) ex = -TILE_SIZE;
            if (r==2) ey = TILE_SIZE;
            if (r==3) ey = -TILE_SIZE;

            int nex = enemigo.x + ex;
            int ney = enemigo.y + ey;

            // Validar límites para enemigo
            if (nex >= 0 && nex < 240 && ney >= 0 && ney < 160) {
                enemigo.x = nex;
                enemigo.y = ney;
            }
            // Dibujar en nueva (o misma) posición
            dibujarEntidad(enemigo.x, enemigo.y, enemigo.color);
        }

        // --- 3. COLISIONES ---
        
        // A. Jugador vs Moneda
        if (jugador.x == moneda.x && jugador.y == moneda.y) {
            score++;
            restaurarCasilla(moneda.x, moneda.y);
            moneda.x = snap(mi_random(220));
            moneda.y = snap(mi_random(140));
            dibujarEntidad(moneda.x, moneda.y, moneda.color);
            // Redibujar jugador encima de la moneda nueva si coinciden, o restaurar visualización
            dibujarEntidad(jugador.x, jugador.y, jugador.color);
        }

        // B. Jugador vs Enemigo (Game Over Reset)
        if (jugador.x == enemigo.x && jugador.y == enemigo.y) {
            score = 0;
            // Efecto visual de muerte (parpadeo rojo opcional, aquí reset simple)
            restaurarCasilla(jugador.x, jugador.y);
            jugador.x = snap(0); // Volver al inicio
            jugador.y = snap(0);
            dibujarEntidad(jugador.x, jugador.y, jugador.color);
        }
    }
    return 0;
}
