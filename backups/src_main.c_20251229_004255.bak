#include "kaia_gba.h"
// Definiciones de Hardware (Directas para evitar errores de headers faltantes)
typedef unsigned short u16;
#define REG_DISPCNT  ((volatile u16)0x04000000)
#define VRAM         ((volatile u16*)0x06000000)
#define MODE_3       0x0003
#define BG2_ENABLE   0x0400

// Definición de Colores (Formato BGR 5-5-5)
#define COLOR_RED    0x001F
#define COLOR_BLUE   0x7C00
#define COLOR_GREEN  0x03E0
#define COLOR_BLACK  0x0000

int main() {
    // 1. Configurar pantalla en MODO 3 (Bitmap)
    REG_DISPCNT = MODE_3 | BG2_ENABLE;

    // 2. Puntero a la memoria de video
    u16* video_memory = (u16*)VRAM;

    // 3. Pintar píxel por píxel (240 ancho x 160 alto)
    for (int i = 0; i < 240 * 160; i++) {
        video_memory[i] = COLOR_RED; 
    }

    // 4. Bucle infinito para mantener el programa vivo
    while (1) {
        // La GBA se queda aquí encendida mostrando el rojo
    }

    return 0;
}
