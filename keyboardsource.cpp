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
		nkeys |= PAD_BUTTON_FIRE;
	}

	if(keys[SDLK_RETURN])
	{
		nkeys |= PAD_BUTTON_START;
	}

	return nkeys;
}


void KeyboardSource::poll()
{
	if(listener)
	{
		lastState = keyState;
		keyState = getKeyState();

		int buttonsDown = ((keyState ^ lastState)) & keyState;
		int buttonsUp   = ((keyState ^ lastState)) & lastState;

		for(int i = 0; i < 32; i++)
		{
			//printf("%c", buttonsDown & (1 << (31-i)) ? '1' : '0');
		}
		//printf("\n");

		if(buttonsDown & PAD_BUTTON_UP)
		{
			printf("UP\n");
			listener->buttonDown(GamepadButton::BUTTON_UP);
		}
		if(buttonsDown & PAD_BUTTON_DOWN)
		{
			printf("DOWN\n");
			listener->buttonDown(GamepadButton::BUTTON_DOWN);
		}
		if(buttonsDown & PAD_BUTTON_LEFT)
		{
			printf("LEFT\n");
			listener->buttonDown(GamepadButton::BUTTON_LEFT);
		}
		if(buttonsDown & PAD_BUTTON_RIGHT)
		{
			printf("RIGHT\n");
			listener->buttonDown(GamepadButton::BUTTON_RIGHT);
		}
		if(buttonsDown & PAD_BUTTON_FIRE)
		{
			printf("FIRE\n");
			listener->buttonDown(GamepadButton::BUTTON_FIRE);
		}
		if(buttonsDown & PAD_BUTTON_START)
		{
			printf("START\n");
			listener->buttonDown(GamepadButton::BUTTON_START);
		}

		if(buttonsUp & PAD_BUTTON_UP)
		{
			printf("up\n");
			listener->buttonUp(GamepadButton::BUTTON_UP);
		}
		if(buttonsUp & PAD_BUTTON_DOWN)
		{
			printf("down\n");
			listener->buttonUp(GamepadButton::BUTTON_DOWN);
		}
		if(buttonsUp & PAD_BUTTON_LEFT)
		{
			printf("left\n");
			listener->buttonUp(GamepadButton::BUTTON_LEFT);
		}
		if(buttonsUp & PAD_BUTTON_RIGHT)
		{
			printf("right\n");
			listener->buttonUp(GamepadButton::BUTTON_RIGHT);
		}
		if(buttonsUp & PAD_BUTTON_FIRE)
		{
			printf("fire\n");
			listener->buttonUp(GamepadButton::BUTTON_FIRE);
		}
		if(buttonsUp & PAD_BUTTON_START)
		{
			printf("start\n");
			listener->buttonUp(GamepadButton::BUTTON_START);
		}
	}
}