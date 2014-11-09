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

#include "font5.h"

#include "gamepadinputmanager.h"

Menu::Menu(MenuListener *listener) : listener(listener), menu_sel(0), next_change(0), ldir(-1), child(NULL)
{
	GamepadInputManager::sharedInstance()->playerOne()->addListener(this);
}

Menu::~Menu()
{
	GamepadInputManager::sharedInstance()->playerOne()->removeListener(this);
}

bool Menu::update()
{
	unsigned long cticks = ticks_to_millisecs(gettime());

	if(cticks>next_change && next_change != 0)
	{
		next_change = cticks+200;
		if(ldir == 1)
		{
			if(menu_sel<3)
			{
				menu_sel++;
			}
			else
			{
				menu_sel = 0;
			}
		}
		else if(ldir == 0)
		{
			if(menu_sel>0)
			{
				menu_sel--;
			}
			else
			{
				menu_sel = 3;
			}
		}
	}

	return true;
}

void Menu::render(GfxWrapper *gfx)
{
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
}

void Menu::incrementMenu()
{
	if(menu_sel<3)
	{
		menu_sel++;
	}
	else
	{
		menu_sel = 0;
	}
}

void Menu::decrementMenu()
{
	if(menu_sel>0)
	{
		menu_sel--;
	}
	else
	{
		menu_sel = 3;
	}
}

void Menu::handleMenuSelection()
{
	switch(menu_sel)
	{
		case 0:
			listener->menuStartGameSelected();
			break;
		case 1:

			listener->menuOptionsSelected();
			break;
		case 2:

			listener->menuAboutSelected();
			break;
		case 3:
			exit(0);
			break;
	}
}

void Menu::buttonDown(GamepadButton button)
{
	if(button == BUTTON_UP)
	{
		ldir = 0;
		decrementMenu();
		next_change = ticks_to_millisecs(gettime()) + 500;
	}
	if(button == BUTTON_DOWN)
	{
		ldir = 1;
		incrementMenu();

		next_change = ticks_to_millisecs(gettime()) + 500;
	}

}

void Menu::buttonUp(GamepadButton button)
{
	next_change = 0;
	ldir = -1;
	
	if(button == BUTTON_FIRE || button == BUTTON_START)
	{
		handleMenuSelection();
	}

}
