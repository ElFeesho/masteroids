#include "menuscreen.h"

MenuScreen::MenuScreen(MenuScreenListener &menuScreenListener) : menuListener(menuScreenListener), menuScreen(this), optionsScreen(this), controllerConfigScreen(this), aboutScreen(this)  {}

MenuScreen::~MenuScreen() {}

void MenuScreen::screenShown()
{
    for (int i = 0; i < 16; i++)
	{
        entityList.add(asteroidFactory.createAsteroid(75.0f));
	}

    activeMenu = &menuScreen;
    activeMenu->menuScreenPresented();
}

void MenuScreen::screenHidden()
{
    entityList.clear();
    activeMenu->menuScreenHidden();
}

void MenuScreen::aboutClosed()
{
    activateScreen(&menuScreen);
}

void MenuScreen::controlConfClosed()
{
    activateScreen(&optionsScreen);
}

void MenuScreen::menuStartGameSelected()
{
    menuListener.menuScreenShouldShowGameScreen();
}

void MenuScreen::menuOptionsSelected()
{
    activateScreen(&optionsScreen);
}

void MenuScreen::menuAboutSelected()
{
    activateScreen(&aboutScreen);
}

void MenuScreen::optionsControllerConfigSelected()
{
    activateScreen(&controllerConfigScreen);
}

void MenuScreen::optionsMenuClosed()
{
    activateScreen(&menuScreen);
}

void MenuScreen::update(GfxWrapper &gfx)
{
	entityList.updateAll();
	activeMenu->update();
	entityList.renderAll(gfx);
	activeMenu->render(gfx);
}

void MenuScreen::setListener(ScreenListener *listener)
{
	this->listener = listener;
}

void MenuScreen::activateScreen(MenuScreenItem *screenItem)
{
    activeMenu->menuScreenHidden();
    activeMenu = screenItem;
    activeMenu->menuScreenPresented();
}
