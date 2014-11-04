#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "engine.h"
#include "options.h"
#include "about.h"
#include <ogcsys.h>
#include <gccore.h>

#include <ogc/lwp_watchdog.h>

#include "asteroid_banner.h"
#include "controllers.h"

#include "GRRLIB.h"

#include "font5.h"

#include "controlconf.h"

Menu::Menu() : menu_sel(0), next_change(ticks_to_millisecs(gettime())+500), ldir(1), child(NULL), borderColour(RGB(0.0f, 0.0f, 1.0f)), textColour(RGB(1.0f, 1.0f, 1.0f)), highlightColour(RGB(1.0f, 0.8f, 0.0f))
{

}

Menu::~Menu()
{

}

bool Menu::update(GfxWrapper *gfx)
{
	if(child)
	{
		if(!child->update(gfx))
		{
			delete child;
			child = NULL;
		}
		return true;
	}
	
	unsigned long cticks = ticks_to_millisecs(gettime());

	if(ControlConf::button_held(0,BUTTON_UP) && cticks>next_change)
	{
		if(ldir == 0)
			next_change = cticks+200;
		else
			next_change = cticks+500;
		ldir = 0;
		if(menu_sel>0)
			menu_sel--;
		else
			menu_sel = 3;
	}

	if(ControlConf::button_held(0,BUTTON_DOWN) && cticks>next_change)
	{
		if(ldir == 1)
			next_change = cticks+200;
		else
			next_change = cticks+500;
		ldir = 1;
		if(menu_sel<3)
			menu_sel++;
		else
			menu_sel = 0;
	}

	if(!ControlConf::button_held(0,BUTTON_UP) && ldir == 0)
	{
		next_change = 0;
	}

	if(!ControlConf::button_held(0,BUTTON_DOWN) && ldir == 1)
	{
		next_change = 0;
	}

	if(ControlConf::button_down(0,BUTTON_SHOOT))
	{
		switch(menu_sel)
		{
			case 0:
				get_engine()->set_mode(1); // Start a single player game
				break;
			case 1:
				child = new Options();
				return true;
				break;
			case 2:
				child = new About();
				return true;
				break;
			case 3:
				exit(0);
				break;
		}
	}
	
	
	gfx->drawRect(320-asteroid_banner_width/2,79,310, asteroid_banner_width+1, borderColour);
	gfx->drawImg(321-asteroid_banner_width/2,80, asteroid_banner_width, asteroid_banner_height, asteroid_banner_data);
	gfx->drawImg(320, 200,controllers_width, controllers_height, controllers_data);
	if(menu_sel==0)
	{
		gfx->drawText(320-asteroid_banner_width/2+20, 80+asteroid_banner_height+font5_char_high+15, (char*)"Start Game", highlightColour);
	}
	else
	{
		gfx->drawText(320-asteroid_banner_width/2+20, 80+asteroid_banner_height+font5_char_high+15, (char*)"Start Game",textColour);
	}
	
	if(menu_sel==1)
	{
		gfx->drawText(320-asteroid_banner_width/2+20, 80+asteroid_banner_height+(font5_char_high+15)*2, (char*)"Options",highlightColour);
	}
	else
	{
		gfx->drawText(320-asteroid_banner_width/2+20, 80+asteroid_banner_height+(font5_char_high+15)*2, (char*)"Options",textColour);
	}
	
	if(menu_sel==2)
	{
		gfx->drawText(320-asteroid_banner_width/2+20, 80+asteroid_banner_height+(font5_char_high+15)*3, (char*)"About",highlightColour);
	}
	else
	{
		gfx->drawText(320-asteroid_banner_width/2+20, 80+asteroid_banner_height+(font5_char_high+15)*3, (char*)"About",textColour);
	}
	if(menu_sel==3)
	{
		gfx->drawText(320-asteroid_banner_width/2+20, 80+asteroid_banner_height+(font5_char_high+15)*4, (char*)"Exit To HBC",highlightColour);
	}
	else
	{
		gfx->drawText(320-asteroid_banner_width/2+20, 80+asteroid_banner_height+(font5_char_high+15)*4, (char*)"Exit To HBC",textColour);
	}
	gfx->drawText(320-asteroid_banner_width/2+20, 80+asteroid_banner_height+(font5_char_high+10)*10, (char*)"Coded by Feesh! - gummybassist@gmail.com",textColour);
	return true;	
}
