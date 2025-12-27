```c
#ifndef KAIA_GBA_H
#define KAIA_GBA_H

// Definiciones de tipos básicos
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

// Registros de hardware
#define REG_DISPCNT (*(volatile u16*)0x04000000)
#define REG_DISPSTAT (*(volatile u16*)0x04000004)
#define REG_VCOUNT (*(volatile u16*)0x04000006)
#define REG_KEYINPUT (*(volatile u16*)0x04000130)
#define REG_KEYCNT (*(volatile u16*)0x04000132)

// Constantes para el Modo 3
#define MODE_3 0x0003

// Constantes para los botones
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

#endif  // KAIA_GBA_H
```