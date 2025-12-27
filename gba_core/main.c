#include "kaia_gba.h"

// --- CONSTANTES ---
#define NEGRO 0x0000
#define AZUL  0x7C00

// --- ESTRUCTURAS ---
typedef struct {
    int x, y;
    int w, h;     // Ancho y Alto
    u16 color;
} Player;

// --- FUNCIONES (Definidas ANTES de usarse) ---

void vid_vsync() {
    while(REG_VCOUNT >= 160); // Esperar fin de VBlank
    while(REG_VCOUNT < 160);  // Esperar inicio de VBlank
}

// Dibuja al jugador usando sus propias coordenadas y color
void dibujarJugador(Player *p, u16 color_override) {
    u16 color_final = (color_override == 0) ? p->color : color_override;
    
    // Validar límites de dibujo para no romper memoria
    for(int i = 0; i < p->w; i++) {
        for(int j = 0; j < p->h; j++) {
            int px = p->x + i;
            int py = p->y + j;
            
            // Solo pintar si está dentro de pantalla (Safety Check)
            if(px >= 0 && px < 240 && py >= 0 && py < 160) {
                VRAM[py * 240 + px] = color_final;
            }
        }
    }
}

// --- MAIN ---
int main() {
    REG_DISPCNT = MODE_3 | BG2_ENABLE;

    // Inicializar Jugador
    Player p = {120, 80, 16, 16, AZUL};

    // Limpieza inicial
    for(int i=0; i<38400; i++) VRAM[i] = NEGRO;

    while (1) {
        // 1. Borrar (Pintar NEGRO en posición vieja)
        dibujarJugador(&p, NEGRO);

        // 2. Input y Física (Con Límites)
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

        // 3. Dibujar (Pintar color del jugador en posición nueva)
        dibujarJugador(&p, 0); // 0 indica "usa el color del struct"

        // 4. Sincronizar
        vid_vsync();
    }

    return 0;
}