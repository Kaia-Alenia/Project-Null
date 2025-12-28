#include <stdint.h>

// --- REGISTROS GBA ---
#define REG_DISPCNT  (*(volatile uint16_t*)0x04000000)
#define VRAM         ((volatile uint16_t*)0x06000000)

// --- CONFIGURACIÓN ---
#define MODE_3       0x0003  // Modo Bitmap
#define BG2_ENABLE   0x0400  // Activar Fondo 2

// --- COLORES (5 bits: 0-31) ---
#define RED          0x001F
#define BLUE         0x7C00
#define GREEN        0x03E0

int main() {
    // 1. Configurar pantalla
    REG_DISPCNT = MODE_3 | BG2_ENABLE;

    // 2. Pintar la pantalla de ROJO
    for (int i = 0; i < 240 * 160; i++) {
        VRAM[i] = RED;
    }

    // 3. Bucle infinito (para que no se apague)
    while (1) {
    }

    return 0;
}
