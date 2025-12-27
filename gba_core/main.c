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

// Definiciones de colores
#define COLOR_ROJO 0x001F

// Estructura para el jugador
typedef struct {
    int x;
    int y;
} Jugador;

// Estructura para el enemigo
typedef struct {
    int x;
    int y;
    int contador;
    int direccion;
} Enemigo;

// Función para inicializar el jugador
Jugador inicializarJugador() {
    Jugador jugador;
    jugador.x = 0;
    jugador.y = 0;
    return jugador;
}

// Función para inicializar el enemigo
Enemigo inicializarEnemigo() {
    Enemigo enemigo;
    enemigo.x = 224;
    enemigo.y = 144;
    enemigo.contador = 0;
    enemigo.direccion = 0; // 0: arriba, 1: abajo, 2: izquierda, 3: derecha
    return enemigo;
}

// Función para restaurar casilla
void restaurarCasilla(int x, int y) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            *(volatile unsigned short*)(0x06000000 + (y * 240) + x + (i * 240) + j) = 0;
        }
    }
}

// Función para dibujar al jugador
void dibujarJugador(Jugador jugador) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            *(volatile unsigned short*)(0x06000000 + (jugador.y * 240) + jugador.x + (i * 240) + j) = 0x07E0;
        }
    }
}

// Función para dibujar al enemigo
void dibujarEnemigo(Enemigo enemigo) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            *(volatile unsigned short*)(0x06000000 + (enemigo.y * 240) + enemigo.x + (i * 240) + j) = COLOR_ROJO;
        }
    }
}

int main() {
    // Inicializar el modo de video
    *(volatile unsigned short*)0x04000000 = MODE_3 | BG2_ENABLE;

    // Inicializar el jugador y el enemigo
    Jugador jugador = inicializarJugador();
    Enemigo enemigo = inicializarEnemigo();

    // Inicializar el score
    int score = 0;

    while (1) {
        // Leer la entrada del usuario
        unsigned short tecla = *(volatile unsigned short*)0x04000130;

        // Mover al jugador
        if (tecla & KEY_UP) {
            jugador.y -= 1;
        }
        if (tecla & KEY_DOWN) {
            jugador.y += 1;
        }
        if (tecla & KEY_LEFT) {
            jugador.x -= 1;
        }
        if (tecla & KEY_RIGHT) {
            jugador.x += 1;
        }

        // Mover al enemigo
        enemigo.contador++;
        if (enemigo.contador >= 30) {
            enemigo.contador = 0;
            // Seleccionar una dirección aleatoria
            enemigo.direccion = (enemigo.direccion + 1) % 4;

            // Mover al enemigo
            if (enemigo.direccion == 0) {
                enemigo.y -= 1;
            } else if (enemigo.direccion == 1) {
                enemigo.y += 1;
            } else if (enemigo.direccion == 2) {
                enemigo.x -= 1;
            } else if (enemigo.direccion == 3) {
                enemigo.x += 1;
            }
        }

        // Colisión con el enemigo
        if (jugador.x < enemigo.x + 16 && jugador.x + 16 > enemigo.x && jugador.y < enemigo.y + 16 && jugador.y + 16 > enemigo.y) {
            score = 0;
            jugador.x = 0;
            jugador.y = 0;
        }

        // Dibujar al jugador y al enemigo
        restaurarCasilla(jugador.x, jugador.y);
        restaurarCasilla(enemigo.x, enemigo.y);
        dibujarJugador(jugador);
        dibujarEnemigo(enemigo);

        // Incrementar el score
        score++;

        // Esperar a que pase un frame
        while (*(volatile unsigned short*)0x04000006 != 160);
    }

    return 0;
}