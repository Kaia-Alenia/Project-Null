#ifndef KAIA_GBA_H
#define KAIA_GBA_H

// --- TIPOS DE DATOS (Estándar GBA) ---
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef volatile u8       vu8;
typedef volatile u16      vu16;
typedef volatile u32      vu32;

// --- REGISTROS DE MEMORIA ---
#define REG_DISPCNT  (*(vu16*)0x04000000)
#define REG_VCOUNT   (*(vu16*)0x04000006)
#define REG_KEYINPUT (*(vu16*)0x04000130)

// --- VIDEO ---
#define VRAM        ((vu16*)0x06000000)
#define MODE_3      0x0003 // Modo Bitmap 240x160 (Color real)
#define BG2_ENABLE  0x0400

#define SCREEN_W    240
#define SCREEN_H    160

// --- COLORES (Macro RGB15) ---
// La GBA usa 5 bits por canal (0-31). Formato: 0RRRRRGGGGGBBBBB
#define RGB15(r, g, b)  ((r) | ((g)<<5) | ((b)<<10))

// Paleta básica para Lia
#define BLACK   RGB15(0,0,0)
#define WHITE   RGB15(31,31,31)
#define RED     RGB15(31,0,0)
#define GREEN   RGB15(0,31,0)
#define BLUE    RGB15(0,0,31)
#define YELLOW  RGB15(31,31,0)
#define CYAN    RGB15(0,31,31)
#define MAGENTA RGB15(31,0,31)

// --- INPUTS (Todos los Botones) ---
// En GBA, 0 = Presionado, 1 = Suelto
#define KEY_A      0x0001
#define KEY_B      0x0002
#define KEY_SELECT 0x0004
#define KEY_START  0x0008
#define KEY_RIGHT  0x0010
#define KEY_LEFT   0x0020
#define KEY_UP     0x0040
#define KEY_DOWN   0x0080
#define KEY_R      0x0100
#define KEY_L      0x0200

// Macro útil para preguntar "¿Está presionado?"
#define KEY_DOWN_NOW(key)  (~(REG_KEYINPUT) & key)

#endif
