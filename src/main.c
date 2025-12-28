#include "kaia_gba.h"

int main() {
	// Código de inicialización y configuración del GBA
	REG_DISPCNT = MODE_3 | BG2_ENABLE;
	
	while (1) {
		// Código de juego o aplicación
	}
	
	return 0;
}