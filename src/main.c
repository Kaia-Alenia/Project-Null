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
    Character player = {100, 100, COLOR_BLUE};
    Character enemy = {200, 100, COLOR_RED};

    // 4. Pintar fondo negro
    for (int i = 0; i < SCREEN_W * SCREEN_H; i++) {
        video_memory[i] = COLOR_BLACK;
    }

    // 5. Dibujar personajes
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            video_memory[(player.y + y) * SCREEN_W + player.x + x] = player.color;
            video_memory[(enemy.y + y) * SCREEN_W + enemy.x + x] = enemy.color;
        }
    }

    int enemy_direction = 1; // Dirección del movimiento automático del enemigo

    // 6. Bucle infinito para mantener el programa vivo
    while (1) {
        // Leer entrada del usuario para el jugador
        u16 keys = REG_KEYINPUT;

        // Mover jugador
        if (keys & KEY_RIGHT) {
            player.x += 1;
        }
        if (keys & KEY_LEFT) {
            player.x -= 1;
        }
        if (keys & KEY_UP) {
            player.y -= 1;
        }
        if (keys & KEY_DOWN) {
            player.y += 1;
        }

        // Mover enemigo de manera automática
        enemy.x += enemy_direction;
        if (enemy.x > SCREEN_W - 10 || enemy.x < 0) {
            enemy_direction *= -1; // Cambiar la dirección si se sale de la pantalla
        }

        // Limpiar pantalla
        for (int i = 0; i < SCREEN_W * SCREEN_H; i++) {
            video_memory[i] = COLOR_BLACK;
        }

        // Dibujar personajes en sus nuevas posiciones
        for (int y = 0; y < 10; y++) {
            for (int x = 0; x < 10; x++) {
                if (player.x + x >= 0 && player.x + x < SCREEN_W && player.y + y >= 0 && player.y + y < SCREEN_H) {
                    video_memory[(player.y + y) * SCREEN_W + player.x + x] = player.color;
                }
                if (enemy.x + x >= 0 && enemy.x + x < SCREEN_W && enemy.y + y >= 0 && enemy.y + y < SCREEN_H) {
                    video_memory[(enemy.y + y) * SCREEN_W + enemy.x + x] = enemy.color;
                }
            }
        }
    }

    return 0;
}