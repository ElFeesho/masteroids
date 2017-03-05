#ifdef __WII__
#include "gamecubepadsource.h"
#include <ogc/pad.h>

GamepadButton &GamecubePadSource::fire()
{
	return fireButton;
}

GamepadButton &GamecubePadSource::up()
{
	return upButton;
}

GamepadButton &GamecubePadSource::left()
{
	return leftButton;
}

GamepadButton &GamecubePadSource::down()
{
	return downButton;
}

GamepadButton &GamecubePadSource::right()
{
	return rightButton;
}

GamepadButton &GamecubePadSource::pause()
{
	return pauseButton;
}

void GamecubePadSource::poll()
{
	if (PAD_ButtonsDown(padNumber) & PAD_BUTTON_UP)
	{
		upButton.notifyDownHandlers();
	}
	if (PAD_ButtonsDown(padNumber) & PAD_BUTTON_DOWN)
	{
		downButton.notifyDownHandlers();
	}
	if (PAD_ButtonsDown(padNumber) & PAD_BUTTON_LEFT)
	{
		leftButton.notifyDownHandlers();
	}
	if (PAD_ButtonsDown(padNumber) & PAD_BUTTON_RIGHT)
	{
		rightButton.notifyDownHandlers();
	}
	if (PAD_ButtonsDown(padNumber) & PAD_BUTTON_A)
	{
		fireButton.notifyDownHandlers();
	}
	if (PAD_ButtonsDown(padNumber) & PAD_BUTTON_START)
	{
		pauseButton.notifyDownHandlers();
	}

	if (PAD_ButtonsUp(padNumber) & PAD_BUTTON_UP)
	{
		upButton.notifyUpHandlers();
	}
	if (PAD_ButtonsUp(padNumber) & PAD_BUTTON_DOWN)
	{
		downButton.notifyUpHandlers();
	}
	if (PAD_ButtonsUp(padNumber) & PAD_BUTTON_LEFT)
	{
		leftButton.notifyUpHandlers();
	}
	if (PAD_ButtonsUp(padNumber) & PAD_BUTTON_RIGHT)
	{
		rightButton.notifyUpHandlers();
	}
	if (PAD_ButtonsUp(padNumber) & PAD_BUTTON_A)
	{
		fireButton.notifyUpHandlers();
	}
	if (PAD_ButtonsUp(padNumber) & PAD_BUTTON_START)
	{
		pauseButton.notifyUpHandlers();
	}


}

#endif
