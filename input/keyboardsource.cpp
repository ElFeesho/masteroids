#ifndef __WII__

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


GamepadButton &KeyboardSource::fire()
{
	return fireButton;
}

GamepadButton &KeyboardSource::up()
{
	return upButton;
}

GamepadButton &KeyboardSource::left()
{
	return leftButton;
}

GamepadButton &KeyboardSource::down()
{
	return downButton;
}

GamepadButton &KeyboardSource::right()
{
	return rightButton;
}

GamepadButton &KeyboardSource::pause()
{
	return pauseButton;
}

void KeyboardSource::poll()
{
	lastState = keyState;
	keyState = getKeyState();

	int buttonsDown = ((keyState ^ lastState)) & keyState;
	int buttonsUp = ((keyState ^ lastState)) & lastState;

	if (buttonsDown & PAD_BUTTON_UP)
	{
		upButton.notifyDownHandlers();
	}
	if (buttonsDown & PAD_BUTTON_DOWN)
	{
		downButton.notifyDownHandlers();
	}
	if (buttonsDown & PAD_BUTTON_LEFT)
	{
		leftButton.notifyDownHandlers();
	}
	if (buttonsDown & PAD_BUTTON_RIGHT)
	{
		rightButton.notifyDownHandlers();
	}
	if (buttonsDown & PAD_BUTTON_FIRE)
	{
		fireButton.notifyDownHandlers();
	}
	if (buttonsDown & PAD_BUTTON_START)
	{
		pauseButton.notifyDownHandlers();
	}

	if (buttonsUp & PAD_BUTTON_UP)
	{
		upButton.notifyUpHandlers();
	}
	if (buttonsUp & PAD_BUTTON_DOWN)
	{
		downButton.notifyUpHandlers();
	}
	if (buttonsUp & PAD_BUTTON_LEFT)
	{
		leftButton.notifyUpHandlers();
	}
	if (buttonsUp & PAD_BUTTON_RIGHT)
	{
		rightButton.notifyUpHandlers();
	}
	if (buttonsUp & PAD_BUTTON_FIRE)
	{
		fireButton.notifyUpHandlers();
	}
	if (buttonsUp & PAD_BUTTON_START)
	{
		pauseButton.notifyUpHandlers();
	}


}

#endif
