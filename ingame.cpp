#include "ingame.h"

InGame::InGame(Gamepad *gamepad, InGameListener *listener)
		: ingameRenderer(InGameMenuRenderer()), gamepad(gamepad), listener(listener), menu_sel(0)
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

void InGame::render(GfxWrapper *gfx)
{
	renderer().render(gfx, position(), shape(), direction());
}

bool InGame::buttonDown(GamepadButton button)
{
	if (button == BUTTON_LEFT)
	{
		menu_sel = 0;
	}
	else if (button == BUTTON_RIGHT)
	{
		menu_sel = 1;
	}
	ingameRenderer.setMenuSelection(menu_sel);
	return false;
}

bool InGame::buttonUp(GamepadButton button)
{
	if (button == BUTTON_FIRE || button == BUTTON_START)
	{
		if (menu_sel == 0)
		{
			listener->ingameContinueSelected();
		}
		else
		{
			listener->ingameQuitSelected();
		}
		return true;
	}
	return false;
}
