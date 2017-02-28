#ifndef __GCCORE_H__
#define __GCCORE_H__

#define PAD_TRIGGER_Z (1 << 0)
#define PAD_BUTTON_DOWN (1 << 1)
#define PAD_BUTTON_UP (1 << 2)
#define PAD_BUTTON_LEFT (1 << 3)
#define PAD_BUTTON_RIGHT (1 << 4)
#define PAD_BUTTON_A (1 << 5)
#define PAD_BUTTON_B (1 << 6)
#define PAD_BUTTON_X (1 << 7)
#define PAD_BUTTON_Y (1 << 8)
#define PAD_BUTTON_START (1 << 9)

void PAD_Init();

void VIDEO_Init();

void VIDEO_WaitVSync();

void PAD_ScanPads();

int PAD_ButtonsDown(int padNumber);

int PAD_ButtonsHeld(int padNumber);

#endif