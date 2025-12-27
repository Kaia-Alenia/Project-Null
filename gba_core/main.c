#include "kaia_gba.h"

void vid_vsync() { 
    while(REG_VCOUNT >= 160); 
    while(REG_VCOUNT < 160); 
}

int main() {
    REG_DISPCNT = MODE_3 | BG2_ENABLE;
    int x = 0;
    int y = 0;
    int old_x = x;
    int old_y = y;
    int color_azul = RGB(0, 0, 255);
    int color_negro = RGB(0, 0, 0);

    while(1) {
        vid_vsync();
        if (!(REG_KEYINPUT & KEY_RIGHT)) {
            old_x = x;
            x++;
            if(x > 239) {
                x = 0;
            }
        }

        // Limpia la posición vieja
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++) {
                plotPixel(old_x + i, old_y + j, color_negro);
            }
        }

        // Pinta la nueva posición
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++) {
                plotPixel(x + i, y + j, color_azul);
            }
        }
    }
    return 0;
}