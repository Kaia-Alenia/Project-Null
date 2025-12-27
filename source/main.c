#include <nds.h>

int main() {
    // Inicializar el modo de video
    videoSetMode(MODE_3_2D);
    videoSetModeSub(MODE_3_2D);

    // Configurar la paleta para el color rojo
    u16 color = RGB15(31, 0, 0); // Rojo
    for (int i = 0; i < 256; i++) {
        paletteMem[i] = color;
    }

    // Llenar la pantalla con el color rojo
    for (int y = 0; y < 240; y++) {
        for (int x = 0; x < 160; x++) {
            *(u16*)(0x06000000 + (y * 160 + x) * 2) = color;
        }
    }

    while(1) {
        // Bucle infinito para mantener la pantalla
        scanKeys();
        if (keysCurrent() & KEY_START) break;
    }

    return 0;
}