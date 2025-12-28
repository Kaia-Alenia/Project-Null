#include "kaia_gba.h"

// Definir constantes para la pantalla
#define SCREEN_W 240
#define SCREEN_H 160

// Definir constantes para los personajes
#define PERSONAJE_ANCHO 16
#define PERSONAJE_ALTO 16

// Definir estructura para los personajes
typedef struct {
    int x;
    int y;
    int vida;
} Personaje;

// Definir los personajes
Personaje personaje1 = {100, 100, 100};
Personaje personaje2 = {200, 200, 100};

// Función para dibujar un personaje en la pantalla
void dibujarPersonaje(Personaje* personaje) {
    // Dibujar el personaje en la pantalla
    for (int y = 0; y < PERSONAJE_ALTO; y++) {
        for (int x = 0; x < PERSONAJE_ANCHO; x++) {
            // Dibujar un pixel en la pantalla
            ((volatile unsigned short*)0x06000000)[(personaje->y + y) * SCREEN_W + personaje->x + x] = 0x7FFF;
        }
    }
}

// Función para verificar si dos personajes se tocan
int personajesSeTocan(Personaje* personaje1, Personaje* personaje2) {
    // Verificar si los personajes se tocan
    if (personaje1->x < personaje2->x + PERSONAJE_ANCHO &&
        personaje1->x + PERSONAJE_ANCHO > personaje2->x &&
        personaje1->y < personaje2->y + PERSONAJE_ALTO &&
        personaje1->y + PERSONAJE_ALTO > personaje2->y) {
        return 1;
    }
    return 0;
}

// Función para restar vida a un personaje
void restarVida(Personaje* personaje) {
    personaje->vida -= 10;
    if (personaje->vida < 0) {
        personaje->vida = 0;
    }
}

int main() {
    // Inicializar la pantalla
    *(volatile unsigned short*)0x04000000 = 0x0400 | 0x0003;

    while (1) {
        // Dibujar los personajes en la pantalla
        dibujarPersonaje(&personaje1);
        dibujarPersonaje(&personaje2);

        // Verificar si los personajes se tocan
        if (personajesSeTocan(&personaje1, &personaje2)) {
            // Restar vida a los personajes
            restarVida(&personaje1);
            restarVida(&personaje2);
        }

        // Esperar a que se complete un frame
        while (*(volatile unsigned short*)0x04000006 != 160);
    }

    return 0;
}