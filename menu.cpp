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

Menu::Menu() : menu_sel(0), next_change(ticks_to_millisecs(gettime())+500), ldir(1), child(NULL)
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
	
	
	gfx->drawRect(320-asteroid_banner_width/2,79,asteroid_banner_width+1, 310, RGB::blue);
	gfx->drawImg(321-asteroid_banner_width/2,80, asteroid_banner_width, asteroid_banner_height, asteroid_banner_data);
	gfx->drawImg(320, 200,controllers_width, controllers_height, controllers_data);
	int menuItemHeight = (font5_char_high+15);

	int menuSeparationHeight = 80 + asteroid_banner_height;
	int menuOffsetX = 320-asteroid_banner_width/2+20;

	if(menu_sel==0)
	{
		gfx->drawText(menuOffsetX, menuSeparationHeight+menuItemHeight, "Start Game", RGB::yellow);
	}
	else
	{
		gfx->drawText(menuOffsetX, menuSeparationHeight+menuItemHeight, "Start Game",RGB::white);
	}
	
	if(menu_sel==1)
	{
		gfx->drawText(menuOffsetX, menuSeparationHeight+menuItemHeight*2, "Options",RGB::yellow);
	}
	else
	{
		gfx->drawText(menuOffsetX, menuSeparationHeight+menuItemHeight*2, "Options",RGB::white);
	}
	
	if(menu_sel==2)
	{
		gfx->drawText(menuOffsetX, menuSeparationHeight+menuItemHeight*3, "About",RGB::yellow);
	}
	else
	{
		gfx->drawText(menuOffsetX, menuSeparationHeight+menuItemHeight*3, "About",RGB::white);
	}

	if(menu_sel == 3)
	{
		gfx->drawText(menuOffsetX, menuSeparationHeight+menuItemHeight*4, "Exit To HBC",RGB::yellow);
	}
	else
	{
		gfx->drawText(menuOffsetX, menuSeparationHeight+menuItemHeight*4, "Exit To HBC",RGB::white);
	}
	gfx->drawText(menuOffsetX, 80+asteroid_banner_height+(font5_char_high+10)*10, "Coded by Feesh! - gummybassist@gmail.com",RGB::white);
	return true;	
}
