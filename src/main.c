#include <stdint.h>

int main() {
    volatile unsigned short* oam = (volatile unsigned short*)0x07000000;
    oam[0] = 0x0000; // Y pos
    oam[1] = 0x0000; // X pos
    oam[2] = 0x0000; // Tile index
    oam[3] = 0x0000; // Attributes
    while(1);
}