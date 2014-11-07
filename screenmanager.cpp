#include "screenmanager.h"
#include "gfx.h"
#include "screen.h"
#include "menuscreen.h"

#include <stdio.h>

ScreenManager::ScreenManager() : menuScreen(new MenuScreen())
{
	menuScreen->setListener(this);
	
	activeScreen = menuScreen;
}

ScreenManager::~ScreenManager()
{

}

void ScreenManager::update(GfxWrapper *gfx)
{
	activeScreen->update(gfx);
}

void ScreenManager::screenClosed(Screen *screen, int reason)
{

}