#include "kaia_gba.h"

// --- CONSTANTES ---
#define NEGRO 0x0000
#define AZUL 0x7C00

// --- ESTRUCTURAS ---
typedef struct {
    int x, y;
    int w, h;
    u16 color;
} Player;

// --- FUNCIONES ---

void vid_vsync() {
    while(REG_VCOUNT >= 160);
    while(REG_VCOUNT < 160);
}

// Función simple: Pinta el rectángulo del color que le digas.
void dibujarJugador(Player *p, u16 color) {
    for(int i = 0; i < p->w; i++) {
        for(int j = 0; j < p->h; j++) {
            int px = p->x + i;
            int py = p->y + j;
            
            // Safety Check (Límites de pantalla)
            if(px >= 0 && px < 240 && py >= 0 && py < 160) {
                VRAM[py * 240 + px] = color;
            }
        }
    }
}

// --- MAIN ---
int main() {
    REG_DISPCNT = MODE_3 | BG2_ENABLE;

    // Inicializar Jugador
    Player p = {120, 80, 16, 16, AZUL};
    // Limpieza inicial de pantalla
    for(int i=0; i<38400; i++) VRAM[i] = NEGRO;
    while (1) {
        // 1. BORRAR: Pasamos NEGRO explícitamente
        dibujarJugador(&p, NEGRO);
        // 2. INPUT Y FÍSICA
        if (!(REG_KEYINPUT & KEY_RIGHT)) { 
            if (p.x + p.w < 240) p.x++; 
        }
        if (!(REG_KEYINPUT & KEY_LEFT))  { 
            if (p.x > 0) p.x--; 
        }
        if (!(REG_KEYINPUT & KEY_UP))    { 
            if (p.y > 0) p.y--; 
        }
        if (!(REG_KEYINPUT & KEY_DOWN))  { 
            if (p.y + p.h < 160) p.y++; 
        }
        // 3. DIBUJAR: Pasamos el color del jugador explícitamente
        dibujarJugador(&p, p.color);
        // 4. SYNC
        vid_vsync();
    }
    return 0;
}