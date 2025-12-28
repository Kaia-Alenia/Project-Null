#include <stdint.h>

// --- REGISTROS GBA (El Hardware) ---
#define REG_DISPCNT  (*(volatile uint16_t*)0x04000000)
#define VRAM         ((volatile uint16_t*)0x06000000)
#define REG_KEYINPUT (*(volatile uint16_t*)0x04000130)

// --- CONFIGURACIÓN ---
#define MODE_3       0x0003
#define BG2_ENABLE   0x0400

// --- COLORES ---
#define COLOR_RED    0x001F
#define COLOR_BLACK  0x0000
#define COLOR_GREEN  0x03E0

// --- INPUTS ---
#define KEY_RIGHT    0x0010
#define KEY_LEFT     0x0020
#define KEY_UP       0x0040
#define KEY_DOWN     0x0080

// Dibujar un pixel
void plot(int x, int y, uint16_t color) {
    if(x >= 0 && x < 240 && y >= 0 && y < 160) {
        VRAM[y * 240 + x] = color;
    }
}

// Dibujar jugador
void draw_player(int x, int y, uint16_t color) {
    for(int i=0; i<10; i++) {
        for(int j=0; j<10; j++) {
            plot(x+j, y+i, color);
        }
    }
}

void delay(int n) { volatile int x=0; for(int i=0; i<n; i++) x++; }

// --- EL CEREBRO QUE FALTABA (MAIN) ---
int main() {
    REG_DISPCNT = MODE_3 | BG2_ENABLE; // Encender pantalla

    int x = 120, y = 80; // Posición inicial

    while(1) {
        // 1. Leer botones (0 = presionado)
        if(!(REG_KEYINPUT & KEY_RIGHT)) x++;
        if(!(REG_KEYINPUT & KEY_LEFT))  x--;
        if(!(REG_KEYINPUT & KEY_UP))    y--;
        if(!(REG_KEYINPUT & KEY_DOWN))  y++;

        // 2. Limpiar pantalla (parcial o total)
        // Para simplificar, pintamos negro donde estaba antes o todo (lento pero seguro)
        for(int i=0; i<240*160; i++) VRAM[i] = COLOR_BLACK;

        // 3. Dibujar
        draw_player(x, y, COLOR_GREEN);

        // 4. Esperar
        delay(5000);
    }
    return 0;
}
