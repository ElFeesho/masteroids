#include "ingame.h"
#include "engine.h"
#include <gccore.h>
#include <ogcsys.h>

#include "GRRLIB.h"
#include "font5.h"

#include "controlconf.h"

InGame::InGame(int player) : player_num(player) , menu_sel(0), colour(RGB(1.0f, 1.0f, 1.0f)), colourHighlight(1.0f, 8.0f, 0.0f)
{

}

InGame::~InGame()
{

}

bool InGame::update(GfxWrapper *gfx)
{
	if(ControlConf::button_down(player_num,BUTTON_LEFT))
	{
		menu_sel = 0;
	}

	if(ControlConf::button_down(player_num,BUTTON_RIGHT))
	{
		menu_sel = 1;
	}

	if(ControlConf::button_down(player_num,BUTTON_SHOOT))
	{
		if(menu_sel == 0) // Continue playing, just return false and get gobbled by the engine
		{
			return false;
		}
		else // Otherwise go back to the main menu
		{
			get_engine()->set_mode(0);
			return false;
		}
	}

	gfx->drawRect((320-150), 240-50, 300, 90, RGB::blue);

	gfx->drawText(320-80, 240-40, "Quit Current Game?", colour);
	if(menu_sel==0)
	{
		gfx->drawText(320-140, 240-5, "Continue", colourHighlight);
	}
	else
	{
		gfx->drawText(320-140, 240-5, "Continue", colour);
	}
	if(menu_sel==1)
	{
		gfx->drawText(420, 240-5, "Exit", colourHighlight);
	}
	else
	{
		gfx->drawText(420, 240-5, "Exit", colour);
	}

	return true;
}
