#include "keyboardsource.h"

#include <SDL/SDL.h>

#define PAD_BUTTON_DOWN (1 << 0)
#define PAD_BUTTON_UP (1 << 1)
#define PAD_BUTTON_LEFT (1 << 2)
#define PAD_BUTTON_RIGHT (1 << 3)
#define PAD_BUTTON_FIRE (1 << 4)
#define PAD_BUTTON_START (1 << 5)

static int getKeyState()
{
	int nkeys = 0;
	Uint8 *keys = SDL_GetKeyState(NULL);

	if (keys[SDLK_UP])
	{
		nkeys |= PAD_BUTTON_UP;
	}

	if (keys[SDLK_DOWN])
	{
		nkeys |= PAD_BUTTON_DOWN;
	}

	if (keys[SDLK_LEFT])
	{
		nkeys |= PAD_BUTTON_LEFT;
	}

	if (keys[SDLK_RIGHT])
	{
		nkeys |= PAD_BUTTON_RIGHT;
	}

	if (keys[SDLK_SPACE])
	{
		nkeys |= PAD_BUTTON_FIRE;
	}

	if (keys[SDLK_RETURN])
	{
		nkeys |= PAD_BUTTON_START;
	}

	return nkeys;
}


void KeyboardSource::poll()
{
	if (listener)
	{
		lastState = keyState;
		keyState = getKeyState();

		int buttonsDown = ((keyState ^ lastState)) & keyState;
		int buttonsUp = ((keyState ^ lastState)) & lastState;

		if (buttonsDown & PAD_BUTTON_UP)
		{
			listener->buttonDown(BUTTON_UP);
		}
		if (buttonsDown & PAD_BUTTON_DOWN)
		{
			listener->buttonDown(BUTTON_DOWN);
		}
		if (buttonsDown & PAD_BUTTON_LEFT)
		{
			listener->buttonDown(BUTTON_LEFT);
		}
		if (buttonsDown & PAD_BUTTON_RIGHT)
		{
			listener->buttonDown(BUTTON_RIGHT);
		}
		if (buttonsDown & PAD_BUTTON_FIRE)
		{
			listener->buttonDown(BUTTON_FIRE);
		}
		if (buttonsDown & PAD_BUTTON_START)
		{
			listener->buttonDown(BUTTON_START);
		}

		if (buttonsUp & PAD_BUTTON_UP)
		{
			listener->buttonUp(BUTTON_UP);
		}
		if (buttonsUp & PAD_BUTTON_DOWN)
		{
			listener->buttonUp(BUTTON_DOWN);
		}
		if (buttonsUp & PAD_BUTTON_LEFT)
		{
			listener->buttonUp(BUTTON_LEFT);
		}
		if (buttonsUp & PAD_BUTTON_RIGHT)
		{
			listener->buttonUp(BUTTON_RIGHT);
		}
		if (buttonsUp & PAD_BUTTON_FIRE)
		{
			listener->buttonUp(BUTTON_FIRE);
		}
		if (buttonsUp & PAD_BUTTON_START)
		{
			listener->buttonUp(BUTTON_START);
		}
	}
}
