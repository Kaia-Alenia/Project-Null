// NO incluimos <gba.h> para evitar errores de librerías.
// Definimos los tipos y punteros manualmente.

typedef unsigned short u16;
typedef unsigned int   u32;

#define REG_DISPCNT  *(volatile u16*)0x04000000
#define VRAM         ((volatile u16*)0x06000000)

#define MODE_3       0x0003
#define BG2_ENABLE   0x0400

// Definimos el color Rojo en formato BGR (5 bits por canal)
#define RED          0x001F 

int main() {
    // 1. Configurar la pantalla: Modo 3 (Bitmap) + Background 2 activado
    REG_DISPCNT = MODE_3 | BG2_ENABLE;

    // 2. Pintar la pantalla de ROJO pixel a pixel
    // La pantalla de GBA es de 240x160 pixeles
    for (int i = 0; i < 240 * 160; i++) {
        VRAM[i] = RED;
    }

    // 3. Bucle infinito para que el juego no se termine
    while (1) {
    }

    return 0;
}
