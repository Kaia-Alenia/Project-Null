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

// --- VARIABLES GLOBALES ---
unsigned int seed = 12345;
int score = 0;

// --- FUNCIONES ---

// Generador de números aleatorios (LCG)
int mi_random(int max) {
    seed = seed * 1103515245 + 12345;
    return (unsigned int)(seed / 65536) % max;
}

// Alinear coordenadas a la cuadrícula (Snap to Grid)
int snap(int val) { 
    return (val / TILE_SIZE) * TILE_SIZE; 
}

void vid_vsync() {
    while(REG_VCOUNT >= 160);
    while(REG_VCOUNT < 160);
}

// Dibuja al jugador con un pequeño margen para estética (14x14px dentro de 16x16)
void dibujarJugador(int x, int y, u16 color) {
    for(int i = 1; i < TILE_SIZE-1; i++) { 
        for(int j = 1; j < TILE_SIZE-1; j++) {
            // Safety check
            int px = x + i;
            int py = y + j;
            if(px >= 0 && px < 240 && py >= 0 && py < 160) {
                VRAM[py * 240 + px] = color;
            }
        }
    }
}

// Dibuja la rejilla completa (Fondo Negro + Líneas Grises)
// Se llama UNA SOLA VEZ al inicio.
void dibujarGridCompleto() {
    // 1. Pintar todo negro
    for(int i=0; i<38400; i++) VRAM[i] = NEGRO;
    
    // 2. Líneas Verticales
    for(int x=0; x<240; x+=TILE_SIZE) 
        for(int y=0; y<160; y++) VRAM[y*240+x] = GRIS;
        
    // 3. Líneas Horizontales
    for(int y=0; y<160; y+=TILE_SIZE) 
        for(int x=0; x<240; x++) VRAM[y*240+x] = GRIS;
}

// --- FUNCIÓN CLAVE: RESTAURACIÓN ACTIVA ---
// Borra el contenido de una celda y PINTA DE NUEVO los bordes de la rejilla.
void restaurarCasilla(int x, int y) {
    for(int i = 0; i < TILE_SIZE; i++) {
        for(int j = 0; j < TILE_SIZE; j++) {
            int px = x + i;
            int py = y + j;
            
            if (px >= 0 && px < 240 && py >= 0 && py < 160) {
                // Si el píxel está en el borde superior o izquierdo de la celda, es GRIS.
                // Si es interior, es NEGRO.
                u16 color = (i == 0 || j == 0) ? GRIS : NEGRO;
                VRAM[py * 240 + px] = color;
            }
        }
    }
}

// --- MAIN ---
int main() {
    // Configuración de Pantalla (Mode 3)
    REG_DISPCNT = MODE_3 | BG2_ENABLE;

    // Inicializar Entidades
    Entity jugador = {snap(120), snap(80), AZUL};
    Entity moneda  = {snap(48), snap(48), AMARILLO};

    // Dibujado Inicial
    dibujarGridCompleto();
    dibujarJugador(jugador.x, jugador.y, jugador.color);
    dibujarJugador(moneda.x, moneda.y, moneda.color);

    u16 keys_ant = 0; // Para detectar flancos (pulsaciones)

    while (1) {
        // Sincronización vertical (60 FPS)
        vid_vsync();
        
        // Input: Detectar "Down" (solo el momento en que se presiona)
        u16 keys = REG_KEYINPUT;
        u16 down = (keys_ant ^ keys) & ~keys;
        keys_ant = keys;

        // 1. Calcular Intención de Movimiento
        int dx = 0, dy = 0;
        if (down & KEY_RIGHT) dx = TILE_SIZE;
        if (down & KEY_LEFT)  dx = -TILE_SIZE;
        if (down & KEY_UP)    dy = -TILE_SIZE;
        if (down & KEY_DOWN)  dy = TILE_SIZE;

        // 2. Si hay movimiento, ejecutar lógica de Restauración
        if (dx != 0 || dy != 0) {
            int nx = jugador.x + dx;
            int ny = jugador.y + dy;

            // Validar límites de pantalla
            if (nx >= 0 && nx < 240 && ny >= 0 && ny < 160) {
                // A. BORRAR: Restauramos la casilla vieja (esto arregla la rejilla)
                restaurarCasilla(jugador.x, jugador.y);
                
                // B. ACTUALIZAR coordenadas
                jugador.x = nx;
                jugador.y = ny;
                
                // C. DIBUJAR en la nueva posición
                dibujarJugador(jugador.x, jugador.y, jugador.color);
            }
        }

        // 3. Lógica de Juego (Colisión con Moneda)
        if (jugador.x == moneda.x && jugador.y == moneda.y) {
            score++;
            if(score >= 5) jugador.color = ROJO;
            if(score >= 10) jugador.color = VERDE;
            
            // Borrar moneda vieja (Restaurando rejilla)
            restaurarCasilla(moneda.x, moneda.y); 
            
            // Mover moneda
            moneda.x = snap(mi_random(220));
            moneda.y = snap(mi_random(140));
            
            // Redibujar ambos
            dibujarJugador(moneda.x, moneda.y, moneda.color);
            dibujarJugador(jugador.x, jugador.y, jugador.color);
        }
    }
    return 0;
}
