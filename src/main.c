#include <stdint.h>

volatile uint16_t* REG_DISPCNT = (volatile uint16_t*)0x04000000;
volatile uint16_t* REG_VCOUNT = (volatile uint16_t*)0x04000006;

void main() {
    // Configuración del modo 3 y habilitación de sprites
    *REG_DISPCNT = 0x0400 | 0x0003; // BG2_ENABLE | MODE_3

    // Configuración de los sprites (Modo 0)
    // Nota: La configuración de los sprites se realiza mediante la memoria de objetos (OAM)
    // La OAM se encuentra en la dirección 0x07000000
    volatile uint16_t* OAM = (volatile uint16_t*)0x07000000;

    // Configuración del primer sprite
    OAM[0] = 0x0000; // Y pos
    OAM[1] = 0x0000; // Tile index
    OAM[2] = 0x0000; // Attribute 0
    OAM[3] = 0x0000; // X pos

    while(1) {
        // Bucle principal
    }
}