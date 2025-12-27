typedef unsigned short u16;
typedef unsigned int u32;

// Dirección de la memoria de video (VRAM)
#define VRAM ((volatile u16*) 0x06000000)

// Registro de control de pantalla (REG_DISPCNT)
#define REG_DISPCNT ((volatile u16*) 0x04000000)

// Constantes para el MODO 3 y BG2_ENABLE
#define MODE_3 0x0003
#define BG2_ENABLE 0x0400

// Registro de entrada de botones (REG_KEYINPUT)
#define REG_KEYINPUT ((volatile u16*) 0x04000130)

// Máscaras para detectar los botones
#define KEY_A 0x0001
#define KEY_B 0x0002
#define KEY_SELECT 0x0004
#define KEY_START 0x0008
#define KEY_RIGHT 0x0010
#define KEY_LEFT 0x0020
#define KEY_UP 0x0040
#define KEY_DOWN 0x0080