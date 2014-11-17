#ifndef __WPAD_H__
#define __WPAD_H__

#define WPAD_CHAN_ALL -1

#define WPAD_BUTTON_DOWN (1 << 0)
#define WPAD_BUTTON_UP (1 << 1)
#define WPAD_BUTTON_LEFT (1 << 2)
#define WPAD_BUTTON_RIGHT (1 << 3)
#define WPAD_BUTTON_1 (1 << 4)
#define WPAD_BUTTON_2 (1 << 5)
#define WPAD_BUTTON_A (1 << 6)
#define WPAD_BUTTON_B (1 << 7)
#define WPAD_BUTTON_PLUS (1 << 8)
#define WPAD_BUTTON_MINUS (1 << 9)

#define WPAD_CLASSIC_BUTTON_DOWN (1 << 0)
#define WPAD_CLASSIC_BUTTON_UP (1 << 1)
#define WPAD_CLASSIC_BUTTON_LEFT (1 << 2)
#define WPAD_CLASSIC_BUTTON_RIGHT (1 << 3)
#define WPAD_CLASSIC_BUTTON_1 (1 << 4)
#define WPAD_CLASSIC_BUTTON_2 (1 << 5)
#define WPAD_CLASSIC_BUTTON_A (1 << 6)
#define WPAD_CLASSIC_BUTTON_B (1 << 7)
#define WPAD_CLASSIC_BUTTON_PLUS (1 << 8)
#define WPAD_CLASSIC_BUTTON_MINUS (1 << 9)


#define WPAD_NUNCHUK_BUTTON_Z (1 << 0)
#define WPAD_NUNCHUK_BUTTON_C (1 << 1)

#define WPAD_EXP_NONE (1 << 0)
#define WPAD_EXP_NUNCHUK (1 << 1)
#define WPAD_EXP_CLASSIC (1 << 2)

typedef struct joystick_t {
    int ang;
    double mag;
} joystick_t;

typedef struct nunchuk_t {
    int btns;
    joystick_t js;
} nunchuk_t;

typedef struct classic_t {
    int btns;
} classic_t;

typedef struct expansion_t {
    int type;
    nunchuk_t nunchuk;
    classic_t classic;
} expansion_t;

void WPAD_Init();

void WPAD_ScanPads();

void WPAD_SetIdleTimeout(int timeout);

void WPAD_Disconnect(int channel);

int WPAD_ButtonsDown(int padNumber);

int WPAD_ButtonsHeld(int padNumber);

void WPAD_Expansion(int padNumber, expansion_t *expansion);

#endif