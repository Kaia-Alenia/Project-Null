#include "include/kaia_gba.h"

int main() {
    // Configuración inicial
    *(volatile u16*)REG_DISPCNT = MODE_3 | BG2_ENABLE;

    // Variables del jugador
    int player_x = 100;
    int player_y = 80; // Declaración de player_y

    while (1) {
        // Manejo de eventos
        if (!(REG_KEYINPUT & KEY_UP))    player_y--;
        if (!(REG_KEYINPUT & KEY_DOWN))  player_y++;
        if (!(REG_KEYINPUT & KEY_LEFT))  player_x--;
        if (!(REG_KEYINPUT & KEY_RIGHT)) player_x++;

        // Lógica del juego
        // ...

        // Dibujado en pantalla
        for (int y = 0; y < SCREEN_H; y++) {
            for (int x = 0; x < SCREEN_W; x++) {
                // Dibujar algo en la pantalla
                // ...
            }
        }

        // Actualización de la pantalla
        // ...
    }

    return 0;
}