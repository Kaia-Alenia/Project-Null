#ifndef KAIA_GBA_H
#define KAIA_GBA_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define REG_DISPCNT  (*(volatile u16*)0x04000000)
#define REG_VCOUNT   (*(volatile u16*)0x04000006)
#define REG_KEYINPUT (*(volatile u16*)0x04000130)

#define VRAM ((volatile u16*)0x06000000)

#define MODE_3      0x0003
#define BG2_ENABLE  0x0400

#define KEY_RIGHT  0x0010
#define KEY_LEFT   0x0020
#define KEY_UP     0x0040
#define KEY_DOWN   0x0080

#endif