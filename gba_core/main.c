#include "kaia_gba.h"

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

// Definición de estructuras
typedef struct {
    int x;
    int y;
    int velocidad;
} Enemigo;

// Variables globales
Enemigo enemigo;
int vram[SCREEN_W * SCREEN_H];

// Función de inicialización
void init() {
    // Inicializar el modo de video
    *(volatile u16*)0x04000000 = MODE_3 | BG2_ENABLE;
    
    // Inicializar el enemigo
    enemigo.x = SCREEN_W / 2;
    enemigo.y = SCREEN_H / 2;
    enemigo.velocidad = 1;
}

// Función de actualización del enemigo
void update_enemigo() {
    // Mover el enemigo 3 veces más rápido
    enemigo.x += enemigo.velocidad * 3;
    
    // Revisar si el enemigo ha salido de la pantalla
    if (enemigo.x > SCREEN_W) {
        enemigo.x = 0;
    }
}

// Función de renderizado
void render() {
    // Limpiar la pantalla
    for (int i = 0; i < SCREEN_W * SCREEN_H; i++) {
        vram[i] = 0;
    }
    
    // Dibujar el enemigo
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (enemigo.x + i < SCREEN_W && enemigo.y + j < SCREEN_H) {
                vram[(enemigo.y + j) * SCREEN_W + enemigo.x + i] = 1;
            }
        }
    }
    
    // Copiar el contenido de vram a la memoria de video
    for (int i = 0; i < SCREEN_W * SCREEN_H; i++) {
        *(volatile u16*)(0x06000000 + i * 2) = vram[i];
    }
}

// Función principal
int main() {
    init();
    
    while (1) {
        // Actualizar el enemigo
        update_enemigo();
        
        // Renderizar la pantalla
        render();
        
        // Esperar a que se complete el frame
        while (*(volatile u16*)0x04000006 != 160);
    }
    
    return 0;
}