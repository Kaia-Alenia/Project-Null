#include "sprite_0705.h"

// Definimos las constantes para la pantalla
#define SCREEN_W 240
#define SCREEN_H 160

// Definimos las constantes para el robot
#define ROBOT_W 16
#define ROBOT_H 16

// Definimos la estructura para el robot
typedef struct {
    int x;
    int y;
    int velocidad;
} Robot;

// Creamos un robot
Robot robot;

// Inicializamos el robot
void initRobot() {
    robot.x = SCREEN_W / 2;
    robot.y = SCREEN_H / 2;
    robot.velocidad = 2;
}

// Dibujamos el robot en la pantalla
void drawRobot() {
    // Dibujamos el robot en la pantalla
    for (int i = 0; i < ROBOT_H; i++) {
        for (int j = 0; j < ROBOT_W; j++) {
            // Dibujamos un píxel en la pantalla
            *(volatile unsigned short*)(0x06000000 + (robot.y + i) * SCREEN_W + robot.x + j) = 0x000F;
        }
    }
}

// Movemos el robot
void moveRobot(int direccion) {
    switch (direccion) {
        case 0: // Arriba
            robot.y -= robot.velocidad;
            break;
        case 1: // Abajo
            robot.y += robot.velocidad;
            break;
        case 2: // Izquierda
            robot.x -= robot.velocidad;
            break;
        case 3: // Derecha
            robot.x += robot.velocidad;
            break;
    }
}

// Main loop
int main() {
    // Inicializamos el robot
    initRobot();

    // Configuramos la pantalla
    *(volatile unsigned short*)0x04000000 = MODE_3 | BG2_ENABLE;

    while (1) {
        // Dibujamos el robot en la pantalla
        drawRobot();

        // Movemos el robot según la entrada del usuario
        int entrada = *(volatile unsigned short*)0x04000130;
        if (entrada & KEY_UP) {
            moveRobot(0);
        } else if (entrada & KEY_DOWN) {
            moveRobot(1);
        } else if (entrada & KEY_LEFT) {
            moveRobot(2);
        } else if (entrada & KEY_RIGHT) {
            moveRobot(3);
        }

        // Esperamos un poco para no consumir demasiada CPU
        for (int i = 0; i < 1000; i++) {
            // Nada
        }
    }

    return 0;
}