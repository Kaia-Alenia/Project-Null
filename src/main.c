#include <stdint.h>

// Configuración del modo 3
#define MODE_3 0x0003
#define BG2_ENABLE 0x0400
#define SCREEN_W 240
#define SCREEN_H 160

// Registros
volatile uint16_t* REG_DISPCNT = (volatile uint16_t*)0x04000000;
volatile uint16_t* REG_VCOUNT = (volatile uint16_t*)0x04000006;

// Configuración inicial
void init() {
    *REG_DISPCNT = MODE_3 | BG2_ENABLE;
}

// Dibujo en la pantalla
void draw() {
    uint16_t* vram = (uint16_t*)0x06000000;
    for (int i = 0; i < SCREEN_W * SCREEN_H; i++) {
        vram[i] = 0x7FFF; // Color negro
    }
}

int main() {
    init();
    draw();
    while (1) {
        // Bucle principal
    }
    return 0;
}