#include "include/kaia_gba.h"

int main() {
	// Inicialización del modo 3
	*(volatile unsigned short*)0x04000000 = 0x0003;

	while (1) {
		// Lee la entrada del teclado
		unsigned short keys = *(volatile unsigned short*)0x04000130;

		// Verifica si se presionó la tecla A
		if (keys & 0x0001) {
			// Acción cuando se presiona la tecla A
		}
	}

	return 0;
}