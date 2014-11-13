#include "ingame.h"
#include "engine.h"
#include <gccore.h>
#include <ogcsys.h>

#include "font5.h"

InGame::InGame(Gamepad *gamepad, InGameListener *listener) : ingameRenderer(InGameMenuRenderer()), gamepad(gamepad), listener(listener), menu_sel(0)
{
	gamepad->addListener(this);
}

InGame::~InGame()
{
	gamepad->removeListener(this);
}

bool InGame::update()
{
	return aliveMonitor().alive();
}

void InGame::render(GfxWrapper* gfx)
{
	renderer().render(gfx, position(), shape(), direction());
}

void InGame::buttonDown(GamepadButton button)
{
	if(button == BUTTON_LEFT)
	{
		menu_sel = 0;
	}
	else if(button == BUTTON_RIGHT)
	{
		menu_sel = 1;
	}
}

void InGame::buttonUp(GamepadButton button)
{
	if(button == BUTTON_FIRE)
	{
		if(menu_sel == 0)
		{
			listener->ingameContinueSelected();
		}
		else
		{
			listener->ingameQuitSelected();
		}
	}
}
