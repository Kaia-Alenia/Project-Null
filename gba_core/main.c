#include "kaia_gba.h"

// Definiciones de colores
#define COLOR_GRIS 0xCCCCCC
#define COLOR_NEGRO 0x000000
#define COLOR_JUGADOR 0xFF0000
#define COLOR_MONEDA 0xFFFF00

// Estructura para el jugador y la moneda
typedef struct {
    u16 x, y;
} objeto;

// Función para dibujar la rejilla
void dibujarGrid() {
    u16* vram = (u16*)0x06000000;
    for (u16 y = 0; y < 160; y += 16) {
        for (u16 x = 0; x < 240; x += 16) {
            // Dibujar celda de la rejilla
            for (u16 dy = 0; dy < 16; dy++) {
                for (u16 dx = 0; dx < 16; dx++) {
                    if (dx == 0 || dx == 15 || dy == 0 || dy == 15) {
                        vram[(y + dy) * 240 + x + dx] = COLOR_GRIS;
                    }
                }
            }
        }
    }
}

// Función para dibujar un objeto (jugador o moneda)
void dibujarObjeto(objeto* obj, u16 color) {
    u16* vram = (u16*)0x06000000;
    for (u16 dy = 0; dy < 14; dy++) {
        for (u16 dx = 0; dx < 14; dx++) {
            vram[(obj->y + dy + 1) * 240 + obj->x + dx + 1] = color;
        }
    }
}

// Función para borrar un objeto (jugador o moneda)
void borrarObjeto(objeto* obj) {
    u16* vram = (u16*)0x06000000;
    for (u16 dy = 0; dy < 14; dy++) {
        for (u16 dx = 0; dx < 14; dx++) {
            vram[(obj->y + dy + 1) * 240 + obj->x + dx + 1] = COLOR_NEGRO;
        }
    }
}

// Generador de números aleatorios manual (LCG)
u16 mi_random() {
    static u16 seed = 1;
    seed = (seed * 1103515245 + 12345) % 0x10000;
    return seed;
}

int main() {
    // Inicializar el hardware
    REG_DISPCTL = MODE_0 | BG2_ENABLE;

    // Dibujar la rejilla una sola vez
    dibujarGrid();

    // Inicializar el jugador y la moneda
    objeto jugador = {16, 16};
    objeto moneda = {128, 128};

    // Bucle principal
    while (1) {
        // Esperar al VBlank
        while (REG_VCOUNT >= 160);
        while (REG_VCOUNT < 160);

        // Mover al jugador y la moneda
        if (KEY_DOWN_NOW(BUTTON_LEFT)) {
            jugador.x -= 16;
        }
        if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
            jugador.x += 16;
        }
        if (KEY_DOWN_NOW(BUTTON_UP)) {
            jugador.y -= 16;
        }
        if (KEY_DOWN_NOW(BUTTON_DOWN)) {
            jugador.y += 16;
        }

        // Generar un nuevo número aleatorio para la moneda
        moneda.x = (mi_random() % 15) * 16;
        moneda.y = (mi_random() % 10) * 16;

        // Borrar el jugador y la moneda antiguos
        borrarObjeto(&jugador);
        borrarObjeto(&moneda);

        // Dibujar el jugador y la moneda nuevos
        dibujarObjeto(&jugador, COLOR_JUGADOR);
        dibujarObjeto(&moneda, COLOR_MONEDA);
    }

    return 0;
}