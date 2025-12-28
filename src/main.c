#include <stdint.h>

// Definiciones de constantes
#define MODE_3 0x0003
#define BG2_ENABLE 0x0400
#define SCREEN_W 240
#define SCREEN_H 160

#define KEY_A 0x0001
#define KEY_B 0x0002
#define KEY_RIGHT 0x0010
#define KEY_LEFT 0x0020
#define KEY_UP 0x0040
#define KEY_DOWN 0x0080

// Punteros a registros
volatile uint16_t* REG_DISPCNT = (volatile uint16_t*)0x04000000;
volatile uint16_t* REG_VCOUNT = (volatile uint16_t*)0x04000006;
volatile uint16_t* REG_KEYINPUT = (volatile uint16_t*)0x04000130;

// Puntero a VRAM
volatile uint16_t* VRAM = (volatile uint16_t*)0x06000000;

int main() {
    // Configuración inicial
    *REG_DISPCNT = MODE_3 | BG2_ENABLE;

    while (1) {
        // Bucle principal
        if (*REG_VCOUNT == 160) {
            // Actualización de pantalla
            for (int i = 0; i < SCREEN_W * SCREEN_H; i++) {
                VRAM[i] = 0x7FFF; // Color blanco
            }
        }

        // Lectura de teclas
        uint16_t keys = *REG_KEYINPUT;
        if (keys & KEY_A) {
            // Acción al presionar A
        }
        if (keys & KEY_B) {
            // Acción al presionar B
        }
        if (keys & KEY_RIGHT) {
            // Acción al presionar derecha
        }
        if (keys & KEY_LEFT) {
            // Acción al presionar izquierda
        }
        if (keys & KEY_UP) {
            // Acción al presionar arriba
        }
        if (keys & KEY_DOWN) {
            // Acción al presionar abajo
        }
    }

    return 0;
}