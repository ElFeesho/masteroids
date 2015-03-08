#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

#include "input/gamepadinputmanager.h"
#include "gametime.h"

static std::function<void()> firePressHandler;

static std::function<void()> upPressHandler;
static std::function<void()> downPressHandler;
static std::function<void()> upReleaseHandler;
static std::function<void()> downReleaseHandler;

Menu::Menu(MenuListener *listener)
		: menuRenderer(MenuRenderer()), listener(listener), menu_sel(0), next_change(0), ldir(-1), child(NULL)
{
	firePressHandler = [&](){
		next_change = 0;
		ldir = -1;
		listener->menuOptionsSelected();
	};

	upPressHandler = [&](){
		ldir = 0;
		decrementMenu();
		next_change = GameTime::getMillis() + 500;
	};

	downPressHandler = [&](){
		ldir = 1;
		incrementMenu();

		next_change = GameTime::getMillis() + 500;
	};

	upReleaseHandler = [&](){
		next_change = 0;
		ldir = -1;
	};

	downReleaseHandler = [&](){
		next_change = 0;
		ldir = -1;
	};


	GamepadInputManager::sharedInstance()->inputForPlayer(0).fire().addUpHandler(&firePressHandler);
	GamepadInputManager::sharedInstance()->inputForPlayer(0).up().addDownHandler(&upPressHandler);
	GamepadInputManager::sharedInstance()->inputForPlayer(0).up().addUpHandler(&upReleaseHandler);
	GamepadInputManager::sharedInstance()->inputForPlayer(0).down().addDownHandler(&downPressHandler);
	GamepadInputManager::sharedInstance()->inputForPlayer(0).down().addUpHandler(&downReleaseHandler);
}

Menu::~Menu()
{
	//GamepadInputManager::sharedInstance()->inputForPlayer(0)->removeListener(this);

	GamepadInputManager::sharedInstance()->inputForPlayer(0).fire().removeUpHandler(&firePressHandler);
	GamepadInputManager::sharedInstance()->inputForPlayer(0).up().removeDownHandler(&upPressHandler);
	GamepadInputManager::sharedInstance()->inputForPlayer(0).up().removeUpHandler(&upReleaseHandler);
	GamepadInputManager::sharedInstance()->inputForPlayer(0).down().removeDownHandler(&downPressHandler);
	GamepadInputManager::sharedInstance()->inputForPlayer(0).down().removeUpHandler(&downReleaseHandler);
}

bool Menu::update()
{
	unsigned long cticks = GameTime::getMillis();

	if (cticks > next_change && next_change != 0)
	{
		next_change = cticks + 200;
		if (ldir == 1)
		{
			if (menu_sel < 3)
			{
				menu_sel++;
			}
			else
			{
				menu_sel = 0;
			}
		}
		else if (ldir == 0)
		{
			if (menu_sel > 0)
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
	if (menu_sel < 3)
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
	if (menu_sel > 0)
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
	switch (menu_sel)
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