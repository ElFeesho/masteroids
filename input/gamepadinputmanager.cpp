#include <SDL/SDL.h>
#include <wiiuse/wpad.h>
#include <gccore.h>
#include "gamepadinputmanager.h"

#include "keyboardsource.h"

GamepadInputManager::GamepadInputManager()
		: gamepads{new Gamepad(new KeyboardSource()), new Gamepad(new KeyboardSource()), new Gamepad(new KeyboardSource()), new Gamepad(new KeyboardSource())}
{
}

GamepadInputManager::~GamepadInputManager()
{
}

void GamepadInputManager::poll()
{
	for (int i = 0; i < 4; i++)
	{
		gamepads[i]->poll();
	}
}

bool GamepadInputManager::checkQuit()
{
	bool result = false;
	SDL_Event ev = {0};

	while (SDL_PollEvent(&ev))
	{
		if (ev.type == SDL_QUIT)
		{
			result = true;
			break;
		}
	}
	return result;
}

void GamepadInputManager::initialise()
{
	PAD_Init();
	WPAD_Init();
	WPAD_Disconnect(WPAD_CHAN_ALL);
	WPAD_SetIdleTimeout(120);
}

Gamepad *GamepadInputManager::inputForPlayer(int playerNumber)
{
	return gamepads[playerNumber];
}

GamepadInputManager *GamepadInputManager::sharedInstance()
{
	return instance;
}

GamepadInputManager *GamepadInputManager::instance = new GamepadInputManager();
