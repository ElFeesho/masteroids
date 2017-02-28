#ifndef __WII__

#include "keyboardsource.h"

#include <SFML/Window.hpp>

#define PAD_BUTTON_DOWN (1 << 0)
#define PAD_BUTTON_UP (1 << 1)
#define PAD_BUTTON_LEFT (1 << 2)
#define PAD_BUTTON_RIGHT (1 << 3)
#define PAD_BUTTON_FIRE (1 << 4)
#define PAD_BUTTON_START (1 << 5)
#define PAD_BUTTON_MASK 0x3f

static int getKeyState()
{
    int nkeys = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		nkeys |= PAD_BUTTON_UP;
	}

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		nkeys |= PAD_BUTTON_DOWN;
	}

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		nkeys |= PAD_BUTTON_LEFT;
	}

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		nkeys |= PAD_BUTTON_RIGHT;
	}

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		nkeys |= PAD_BUTTON_FIRE;
	}

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
	{
		nkeys |= PAD_BUTTON_START;
	}

    return nkeys & PAD_BUTTON_MASK;
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

KeyboardSource::KeyboardSource()
{
    printf("KeyboardSource\n");
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
