#include "kaia_gba.h"

int main() {
    // Configuración inicial
    *(volatile u16*)0x04000000 = MODE_3 | BG2_ENABLE;

    while (1) {
        // Lee la entrada del teclado
        u16 keys = *(volatile u16*)0x04000130;

        // Puedes agregar aquí la lógica para manejar las teclas presionadas
        // Por ejemplo, para la tecla A
        if (keys & KEY_A) {
            // Acción cuando se presiona la tecla A
        }

        // Actualiza el contador de cuadros
        u16 vcount = *(volatile u16*)0x04000006;
        // Puedes usar vcount para sincronizar con el framerate de la GBA
    }

    return 0;
}