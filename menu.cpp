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
#include "time.h"

Menu::Menu(MenuListener *listener) : menuRenderer(MenuRenderer()), listener(listener), menu_sel(0), next_change(0), ldir(-1), child(NULL)
{
	GamepadInputManager::sharedInstance()->playerOne()->addListener(this);
}

Menu::~Menu()
{
	GamepadInputManager::sharedInstance()->playerOne()->removeListener(this);
}

bool Menu::update()
{
	unsigned long cticks = Time::getMillis();

	if(cticks > next_change && next_change != 0)
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

	menuRenderer.setMenuItemSelection(menu_sel);
	return true;
}

void Menu::render(GfxWrapper *gfx)
{
	renderer().render(gfx, position(), shape(), direction());
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
		next_change = Time::getMillis() + 500;
	}
	if(button == BUTTON_DOWN)
	{
		ldir = 1;
		incrementMenu();

		next_change = Time::getMillis() + 500;
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
