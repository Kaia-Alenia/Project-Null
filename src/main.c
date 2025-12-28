#include <stdint.h>

// --- DEFINICIONES DE HARDWARE (Eficientes) ---
#define REG_DISPCNT  (*(volatile uint16_t*)0x04000000)
#define VRAM         ((volatile uint16_t*)0x06000000)
#define REG_KEYINPUT (*(volatile uint16_t*)0x04000130)

#define MODE_3       0x0003
#define BG2_ENABLE   0x0400

// Colores
#define NEGRO   0x0000
#define BLANCO  0x7FFF
#define ROJO    0x001F
#define VERDE   0x03E0
#define AZUL    0x7C00

// Teclas (0 = presionado)
#define KEY_A      0x0001
#define KEY_B      0x0002
#define KEY_RIGHT  0x0010
#define KEY_LEFT   0x0020
#define KEY_UP     0x0040
#define KEY_DOWN   0x0080

// Función para retardo (para que no vaya demasiado rápido)
void delay(volatile int n) {
    while(n--) __asm__("nop");
}

int main() {
    // 1. Configurar pantalla
    REG_DISPCNT = MODE_3 | BG2_ENABLE;

    // 2. Coordenadas del jugador
    int x = 120;
    int y = 80;
    uint16_t color_jugador = AZUL;

    while (1) {
        // --- LEER CONTROLES ---
        // Recordatorio: En GBA, presionado es 0 (falso), por eso usamos "!"
        if (!(REG_KEYINPUT & KEY_RIGHT)) x++;
        if (!(REG_KEYINPUT & KEY_LEFT))  x--;
        if (!(REG_KEYINPUT & KEY_UP))    y--;
        if (!(REG_KEYINPUT & KEY_DOWN))  y++;
        
        if (!(REG_KEYINPUT & KEY_A)) color_jugador = ROJO;
        if (!(REG_KEYINPUT & KEY_B)) color_jugador = VERDE;

        // Limites de pantalla (para que no se salga y crashee)
        if(x < 0) x = 0;
        if(x > 230) x = 230;
        if(y < 0) y = 0;
        if(y > 150) y = 150;

        // --- DIBUJAR ---
        // 1. Borrar pantalla (Pintar todo negro)
        // Nota: Esto es "fuerza bruta", parpadeará un poco, pero funciona para aprender.
        for (int i = 0; i < 240 * 160; i++) {
            VRAM[i] = NEGRO;
        }

        // 2. Pintar al jugador (cuadrado de 10x10)
        for(int h=0; h<10; h++){
            for(int w=0; w<10; w++){
                VRAM[(y+h)*240 + (x+w)] = color_jugador;
            }
        }

        // 3. Esperar un poco
        delay(5000);
    }

    return 0;
}
