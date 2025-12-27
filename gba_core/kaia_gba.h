#ifndef KAIA_GBA_H
#define KAIA_GBA_H

// Definiciones de registros
#define REG_DISPCNT  *(volatile unsigned short *)0x04000000
#define REG_KEYINPUT *(volatile unsigned short *)0x04000130
#define REG_KEYCNT  *(volatile unsigned short *)0x04000132

// Definiciones de teclas
#define KEY_A      0x0001
#define KEY_B      0x0002
#define KEY_SELECT 0x0004
#define KEY_START  0x0008
#define KEY_RIGHT  0x0010
#define KEY_LEFT   0x0020
#define KEY_UP     0x0040
#define KEY_DOWN   0x0080

// Definiciones de memoria
#define VRAM       ((volatile unsigned short *)0x06000000)

// Funciones
void vid_vsync();
void dibujarJugador();

#endif