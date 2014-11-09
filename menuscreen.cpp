#include "menuscreen.h"

#include "menu.h"
#include "asteroid.h"
#include <stdio.h>

MenuScreen::MenuScreen()
{
	
}

MenuScreen::~MenuScreen()
{

}

void MenuScreen::screenShown()
{
	menu = new Menu();
	menu->setListener(this);

	for(int i = 0; i < 32; i++)
	{
		entityList.add(new Asteroid());
	}
}

void MenuScreen::screenHidden()
{
	entityList.clear();
	
	delete menu;
	menu = NULL;
}

void MenuScreen::menuStartGameSelected()
{
	listener->screenClosed(this, 1);
}

void MenuScreen::menuOptionsSelected()
{

}

void MenuScreen::menuAboutSelected()
{

}

void MenuScreen::update(GfxWrapper *gfx)
{
	entityList.updateAll();
	menu->update();
	entityList.renderAll(gfx);
	menu->render(gfx);
}

void MenuScreen::setListener(ScreenListener *listener)
{
	this->listener = listener;
}
