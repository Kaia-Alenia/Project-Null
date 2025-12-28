#include "kaia_gba.h"

int main() {
    // Configuración de la pantalla
    *(volatile u16*)0x04000000 = MODE_3 | BG2_ENABLE;
    
    // Bucle principal
    while(1) {
        // Lee el estado de los botones
        u16 keys = *(volatile u16*)0x04000130;
        
        // Puedes agregar aquí la lógica para manejar los botones y actualizar la pantalla
    }
    
    return 0;
}