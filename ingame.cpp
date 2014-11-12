#include "ingame.h"
#include "engine.h"
#include <gccore.h>
#include <ogcsys.h>

#include "font5.h"

InGame::InGame(Gamepad *gamepad, InGameListener *listener) : gamepad(gamepad), listener(listener), menu_sel(0)
{
	gamepad->addListener(this);
}

InGame::~InGame()
{
	gamepad->removeListener(this);
}

bool InGame::update()
{
	return true;
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
void InGame::render(GfxWrapper* gfx)
{
	gfx->drawRect((320-150), 240-50, 300, 90, RGB::blue);

	gfx->drawText(320-80, 240-40, "Quit Current Game?", RGB::white);
	if(menu_sel==0)
	{
		gfx->drawText(320-140, 240-5, "Continue", RGB::yellow);
	}
	else
	{
		gfx->drawText(320-140, 240-5, "Continue", RGB::white);
	}
	
	if(menu_sel==1)
	{
		gfx->drawText(420, 240-5, "Exit", RGB::yellow);
	}
	else
	{
		gfx->drawText(420, 240-5, "Exit", RGB::white);
	}
}
