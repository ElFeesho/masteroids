#ifndef __WII__
#include <SFML/Main.hpp>
#endif
#include <wiiuse/wpad.h>
#include <gccore.h>
#include <iostream>
#include "gamepadinputmanager.h"

#include "keyboardsource.h"
#include "gamecubepadsource.h"

static GamepadInputManager instance;

GamepadInputManager::GamepadInputManager()
#ifndef __WII__
        : gamepad{std::unique_ptr<KeyboardSource>(new KeyboardSource())}
#else
		: gamepads{new GamecubePadSource(0), new GamecubePadSource(1), new GamecubePadSource(2), new GamecubePadSource(3)}
#endif
{
	std::cout << "GamepadInputManager" << std::endl;
}

GamepadInputManager::~GamepadInputManager()
{
    std::cout << "~GamepadInputManager" << std::endl;
}

void GamepadInputManager::poll()
{
	PAD_ScanPads();
	WPAD_ScanPads();
    gamepad->poll();
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

GamepadSource &GamepadInputManager::inputForPlayer(int)
{
    return *(gamepad.get());
}

GamepadInputManager &GamepadInputManager::sharedInstance()
{
    return instance;
}
