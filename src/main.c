#include <stdint.h>

// Definiciones de la GBA
#define REG_DISPCNT  (*(volatile uint16_t*)0x04000000)
#define VRAM         ((volatile uint16_t*)0x06000000)
#define MODE_3       0x0003
#define BG2_ENABLE   0x0400
#define RED          0x001F

int main() {
    // Configurar pantalla
    REG_DISPCNT = MODE_3 | BG2_ENABLE;

    // Pintar rojo
    for (int i = 0; i < 240 * 160; i++) {
        VRAM[i] = RED;
    }

    // Bucle infinito
    while (1) {}
    return 0;
}
