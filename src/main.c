typedef unsigned short u16;
#define REG_DISPCNT  (*(volatile u16*)0x04000000)
#define VRAM         ((volatile u16*)0x06000000)
#define REG_KEYINPUT (*(volatile u16*)0x04000130)
#define MODE_0       0x0000
#define BG2_ENABLE   0x0400
#define KEY_A        0x0001
#define KEY_B        0x0002
#define KEY_RIGHT    0x0010
#define KEY_LEFT     0x0020
#define KEY_UP       0x0040
#define KEY_DOWN     0x0080
#define COLOR_RED    0x001F
#define COLOR_BLUE   0x7C00
#define COLOR_GREEN  0x03E0
#define COLOR_BLACK  0x0000
#define SCREEN_W    240
#define SCREEN_H    160

// Estructura para representar un personaje
typedef struct {
    int x, y; // Posición en la pantalla
    u16 color; // Color del personaje
} Character;

int main() {
    // 1. Configurar pantalla en MODO 0 (Tilemap)
    REG_DISPCNT = MODE_0 | BG2_ENABLE;

    // 2. Puntero a la memoria de video
    u16* video_memory = (u16*)VRAM;

    // 3. Inicializar personajes
    Character player_red = {100, 100, COLOR_RED};
    Character player_blue = {200, 100, COLOR_BLUE};

    // 4. Pintar fondo negro
    for (int i = 0; i < SCREEN_W * SCREEN_H; i++) {
        video_memory[i] = COLOR_BLACK;
    }

    // 5. Dibujar personajes
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            video_memory[(player_red.y + y) * SCREEN_W + player_red.x + x] = player_red.color;
            video_memory[(player_blue.y + y) * SCREEN_W + player_blue.x + x] = player_blue.color;
        }
    }

    int direction = 1; // Dirección del movimiento automático del enemigo rojo

    // 6. Bucle infinito para mantener el programa vivo
    while (1) {
        // Leer entrada del usuario para el jugador azul
        u16 keys = REG_KEYINPUT;

        // Mover jugador azul
        if (keys & KEY_RIGHT) {
            player_blue.x -= 1; // Corregir el movimiento
        }
        if (keys & KEY_LEFT) {
            player_blue.x += 1; // Corregir el movimiento
        }
        if (keys & KEY_UP) {
            player_blue.y += 1; // Corregir el movimiento
        }
        if (keys & KEY_DOWN) {
            player_blue.y -= 1; // Corregir el movimiento
        }

        // Mover enemigo rojo de manera automática
        player_red.x += direction;
        if (player_red.x > SCREEN_W - 10 || player_red.x < 0) {
            direction *= -1; // Cambiar la dirección si se sale de la pantalla
        }

        // Limpiar pantalla
        for (int i = 0; i < SCREEN_W * SCREEN_H; i++) {
            video_memory[i] = COLOR_BLACK;
        }

        // Dibujar personajes en sus nuevas posiciones
        for (int y = 0; y < 10; y++) {
            for (int x = 0; x < 10; x++) {
                if (player_red.x + x >= 0 && player_red.x + x < SCREEN_W && player_red.y + y >= 0 && player_red.y + y < SCREEN_H) {
                    video_memory[(player_red.y + y) * SCREEN_W + player_red.x + x] = player_red.color;
                }
                if (player_blue.x + x >= 0 && player_blue.x + x < SCREEN_W && player_blue.y + y >= 0 && player_blue.y + y < SCREEN_H) {
                    video_memory[(player_blue.y + y) * SCREEN_W + player_blue.x + x] = player_blue.color;
                }
            }
        }
    }

    return 0;
}