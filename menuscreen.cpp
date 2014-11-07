#include "menuscreen.h"

#include "menu.h"
#include "asteroid.h"
#include <stdio.h>

MenuScreen::MenuScreen()
{
	menu = new Menu();
	menu->setListener(this);

	for(int i = 0; i < 32; i++)
	{
		entityList.add(new Asteroid());
	}
}

MenuScreen::~MenuScreen()
{

}


void MenuScreen::menuStartGameSelected()
{
	printf("WOOP\n");
}

void MenuScreen::menuOptionsSelected()
{

}

void MenuScreen::menuAboutSelected()
{

}

void MenuScreen::update(GfxWrapper *gfx)
{
	entityList.updateAll(gfx);
	menu->update(gfx);
}

void MenuScreen::setListener(ScreenListener *listener)
{
	this->listener = listener;
}