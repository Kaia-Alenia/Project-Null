#ifndef KAIA_GBA_H
#define KAIA_GBA_H

// Definiciones de tipos
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

// Registros
#define REG_DISPCNT *(volatile u16*)0x04000000
#define REG_VCOUNT *(volatile u16*)0x04000006
#define REG_KEYINPUT *(volatile u16*)0x04000130

// Constantes MODO 3
#define MODE_3 0x0003
#define BG2_ENABLE 0x0400

// Puntero VRAM
#define VRAM ((volatile u16*)0x06000000)

#endif  // KAIA_GBA_H