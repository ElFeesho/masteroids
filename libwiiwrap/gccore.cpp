#include "gccore.h"

#include <SDL/SDL.h>

static long lastTicks = 0;

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

static int BUTTON_STATE = 0;
static int BUTTON_LASTSTATE = 0;
static int BUTTON_DOWN_STATE = 0;

void VIDEO_Init()
{
	SDL_Init(SDL_INIT_VIDEO);
}

void PAD_Init() 
{
	SDL_Init(SDL_INIT_JOYSTICK);
}

void VIDEO_WaitVSync()
{
	long currentTime = SDL_GetTicks();
	if(currentTime  - lastTicks < (1000/60))
	{
		SDL_Delay((1000/60) - (currentTime - lastTicks));
	}
	lastTicks = SDL_GetTicks();
}

int getButtonState()
{
	int nkeys = 0;
	Uint8 *keys = SDL_GetKeyState(NULL);
	if(keys[SDLK_UP])
	{
		nkeys |= PAD_BUTTON_UP;
	}
	if(keys[SDLK_DOWN])
	{
		nkeys |= PAD_BUTTON_DOWN;
	}
	if(keys[SDLK_LEFT])
	{
		nkeys |= PAD_BUTTON_LEFT;
	}
	if(keys[SDLK_RIGHT])
	{
		nkeys |= PAD_BUTTON_RIGHT;
	}
	if(keys[SDLK_SPACE])
	{
		nkeys |= PAD_BUTTON_A;
	}
	if(keys[SDLK_c])
	{
		nkeys |= PAD_BUTTON_B;
	}
	if(keys[SDLK_RETURN])
	{
		nkeys |= PAD_BUTTON_START;
	}

	return nkeys;
}

void PAD_ScanPads()
{
	BUTTON_DOWN_STATE = 0;
	BUTTON_LASTSTATE = BUTTON_STATE;
	BUTTON_STATE = getButtonState();
	BUTTON_DOWN_STATE = ((BUTTON_STATE ^ BUTTON_LASTSTATE)) & BUTTON_STATE;
}

int PAD_ButtonsDown(int padButton)
{
	return BUTTON_DOWN_STATE;
}

int PAD_ButtonsHeld(int padNumber)
{
	return BUTTON_STATE & BUTTON_LASTSTATE;
}
