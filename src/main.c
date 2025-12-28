#include <stdint.h>

// --- DEFINICIONES DE HARDWARE GBA (BARE METAL) ---
// Al ponerlas aquí, eliminamos la necesidad de .h externos
typedef uint16_t u16;
typedef uint32_t u32;

#define REG_DISPCNT  (*(volatile u16*)0x04000000)
#define VRAM         ((volatile u16*)0x06000000)
#define REG_KEYINPUT (*(volatile u16*)0x04000130)

// Configuración de Pantalla
#define MODE_3       0x0003  // Modo de video bitmap 240x160
#define BG2_ENABLE   0x0400  // Activar fondo 2

// Colores (Formato 0x555 BGR)
#define COLOR_LIA    0x7C00  // Azul/Morado (aprox)
#define COLOR_BLACK  0x0000
#define COLOR_WHITE  0x7FFF

// Botones
#define KEY_A        0x0001
#define KEY_B        0x0002
#define KEY_RIGHT    0x0010
#define KEY_LEFT     0x0020
#define KEY_UP       0x0040
#define KEY_DOWN     0x0080

// --- FUNCIONES GRÁFICAS BÁSICAS ---

// Dibujar un pixel individual
void plot_pixel(int x, int y, u16 color) {
    if (x >= 0 && x < 240 && y >= 0 && y < 160) {
        VRAM[y * 240 + x] = color;
    }
}

// Dibujar un cuadrado (El Jugador)
void draw_rect(int x, int y, int w, int h, u16 color) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            plot_pixel(x + j, y + i, color);
        }
    }
}

// Retardo simple (para que no vaya a 1000fps)
void delay(volatile int amount) {
    while(amount--) __asm__("nop");
}

// --- FUNCIÓN PRINCIPAL (EL MOTOR) ---
int main() {
    // 1. Configurar Pantalla
    REG_DISPCNT = MODE_3 | BG2_ENABLE;

    // 2. Variables de Estado
    int player_x = 110;
    int player_y = 70;
    u16 player_color = COLOR_LIA;

    // 3. Bucle Infinito (Game Loop)
    while (1) {
        // A. Leer Controles (Lógica inversa: 0 = presionado)
        u16 keys = REG_KEYINPUT;
        
        if (!(keys & KEY_RIGHT)) player_x++;
        if (!(keys & KEY_LEFT))  player_x--;
        if (!(keys & KEY_UP))    player_y--;
        if (!(keys & KEY_DOWN))  player_y++;
        
        if (!(keys & KEY_A))     player_color = COLOR_WHITE; // Botón A cambia color
        else                     player_color = COLOR_LIA;

        // B. Limpiar Pantalla (Fuerza bruta, lento pero seguro)
        // En el futuro usaremos "Double Buffering", por ahora esto parpadeará un poco pero funciona.
        for (int i = 0; i < 240 * 160; i++) {
            VRAM[i] = COLOR_BLACK;
        }

        // C. Dibujar Jugador
        draw_rect(player_x, player_y, 10, 10, player_color);

        // D. Sincronización simple
        delay(5000);
    }

    return 0;
¿
