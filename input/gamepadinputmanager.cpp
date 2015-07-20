#ifndef __WII__
#include <SDL/SDL.h>
#endif
#include <wiiuse/wpad.h>
#include <gccore.h>
#include "gamepadinputmanager.h"

#include "keyboardsource.h"
#include "gamecubepadsource.h"

static GamepadInputManager instance;

GamepadInputManager::GamepadInputManager()
#ifndef __WII__
		: gamepads{new KeyboardSource(), new KeyboardSource(), new KeyboardSource(), new KeyboardSource()}
#else
		: gamepads{new GamecubePadSource(0), new GamecubePadSource(1), new GamecubePadSource(2), new GamecubePadSource(3)}
#endif
{
}

GamepadInputManager::~GamepadInputManager()
{
}

void GamepadInputManager::poll()
{
	PAD_ScanPads();
	WPAD_ScanPads();
	for (int i = 0; i < 4; i++)
	{
		gamepads[i]->poll();
	}
}

bool GamepadInputManager::checkQuit()
{
	bool result = false;

#ifdef __WII__
	PAD_ScanPads();
	WPAD_ScanPads();
	//WPAD_ReadPending(WPAD_CHAN_ALL, NULL);
	if (PAD_ButtonsDown(0) & PAD_TRIGGER_Z)
	{
		//exit(0);
	}
	if(!((*(u32*)0xCC003000)>>16))
	{
		result = true;
	}
#else
	SDL_Event ev = {0};

	while (SDL_PollEvent(&ev))
	{
		if (ev.type == SDL_QUIT)
		{
			result = true;
			break;
		}
	}
#endif
	return result;
}

void GamepadInputManager::initialise()
{
	PAD_Init();
	WPAD_Init();
	WPAD_Disconnect(WPAD_CHAN_ALL);
	WPAD_SetIdleTimeout(120);
}

GamepadSource &GamepadInputManager::inputForPlayer(int playerNumber)
{
	return *gamepads[playerNumber];
}

GamepadInputManager &GamepadInputManager::sharedInstance()
{
    return instance;
}
