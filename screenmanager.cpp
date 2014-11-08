#include "screenmanager.h"
#include "gfx.h"
#include "screen.h"
#include "menuscreen.h"
#include "gamescreen.h"
#include <stdio.h>

ScreenManager::ScreenManager() : menuScreen(new MenuScreen()), gameScreen(new GameScreen())
{
	menuScreen->setListener(this);
	gameScreen->setListener(this);
	
	activeScreen = menuScreen;
	menuScreen->screenShown();
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
  if(screen == menuScreen)
  {
	 if(reason == 1)
	 {
		activeScreen = gameScreen;
		menuScreen->screenHidden();
		gameScreen->screenShown();
	 }
  }
  else if(screen == gameScreen)
  {
	  activeScreen = menuScreen;
	  gameScreen->screenHidden();
	  activeScreen->screenShown();
  }
}