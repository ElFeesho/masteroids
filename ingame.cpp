#include "ingame.h"
#include "engine.h"
#include <gccore.h>
#include <ogcsys.h>

#include "GRRLIB.h"
#include "font5.h"

#include "controlconf.h"

InGame::InGame(int player) : player_num(player) , menu_sel(0)
{

}

InGame::~InGame()
{

}

bool InGame::update()
{
	if(ControlConf::button_down(player_num,BUTTON_LEFT))
		menu_sel = 0;
	if(ControlConf::button_down(player_num,BUTTON_RIGHT))
		menu_sel = 1;
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
	
	GRRLIB_DrawRectangle((320-150),240-50,90, 300, 0,1);
	GRRLIB_DrawRectangle((320-150),240-50,90, 300, 0x001f,0);

	GRRLIB_Print(320-80, 240-40, font5_char_width, font5_char_high, (char*)"Quit Current Game?",font5, 0xffff, 0x0000);
	if(menu_sel==0)
		GRRLIB_Print(320-140, 240-5, font5_char_width, font5_char_high, (char*)"Continue",font5, 0xffa0, 0x0000);
	else
		GRRLIB_Print(320-140, 240-5, font5_char_width, font5_char_high, (char*)"Continue",font5, 0xffff, 0x0000);
	if(menu_sel==1)
		GRRLIB_Print(420, 240-5, font5_char_width, font5_char_high, (char*)"Exit",font5, 0xffa0, 0x0000);
	else
		GRRLIB_Print(420, 240-5, font5_char_width, font5_char_high, (char*)"Exit",font5, 0xffff, 0x0000);
	
	return true;
}
