#include <stdint.h>

// --- REGISTROS DE PANTALLA ---
#define REG_DISPCNT  (*(volatile uint16_t*)0x04000000)
#define VRAM         ((volatile uint16_t*)0x06000000)
#define MODE_3       0x0003
#define BG2_ENABLE   0x0400

// --- REGISTROS DE CONTROLES (INPUT) ---
// En GBA, los botones están en la dirección 0x04000130
#define REG_KEYINPUT (*(volatile uint16_t*)0x04000130)

// Máscaras de botones (0 = Presionado, 1 = Suelto)
#define KEY_A        0x0001
#define KEY_B        0x0002
#define KEY_RIGHT    0x0010
#define KEY_LEFT     0x0020
#define KEY_UP       0x0040
#define KEY_DOWN     0x0080

// --- COLORES ---
#define BLACK        0x0000
#define WHITE        0x7FFF
#define BLUE         0x7C00

// Función simple para dibujar un pixel (coordenadas x, y)
void plot_pixel(int x, int y, uint16_t color) {
    VRAM[y * 240 + x] = color;
}

// Función para pintar un cuadrado de 10x10
void draw_rect(int x, int y, uint16_t color) {
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            // Evitar dibujar fuera de pantalla
            if (x+j < 240 && y+i < 160) {
                plot_pixel(x+j, y+i, color);
            }
        }
    }
}

// Una espera tonta para que no vaya a la velocidad de la luz
void delay(int n) {
    volatile int x = 0;
    for(int i=0; i<n; i++) x++;
}

int main() {
    // 1. Configurar pantalla
    REG_DISPCNT = MODE_3 | BG2_ENABLE;

    // Posición inicial del jugador
    int player_x = 120;
    int player_y = 80;

    while (1) {
        // A. LEER BOTONES
        // (En GBA, si el bit es 0, el botón está presionado)
        if (!(REG_KEYINPUT & KEY_RIGHT)) player_x++;
        if (!(REG_KEYINPUT & KEY_LEFT))  player_x--;
        if (!(REG_KEYINPUT & KEY_UP))    player_y--;
        if (!(REG_KEYINPUT & KEY_DOWN))  player_y++;

        // B. LIMPIAR PANTALLA (Borrar el cuadro anterior)
        // (Esto es ineficiente, pero fácil de entender: pintamos todo negro)
        for (int i = 0; i < 240 * 160; i++) VRAM[i] = BLACK;

        // C. DIBUJAR JUGADOR NUEVO
        draw_rect(player_x, player_y, BLUE);

        // D. ESPERAR UN POCO (Para ver el movimiento)
        delay(5000);
    }

    return 0;
}
