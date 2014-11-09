 #include "gamescreen.h"
#include "asteroid.h"
#include "ship.h"
#include "gamepadinputmanager.h"
#include <stdio.h>

GameScreen::GameScreen() : isPaused(false)
{
}

GameScreen::~GameScreen()
{

}

void GameScreen::screenHidden()
{
	entities.clear();
	if(pauseEnt != NULL)
	{
		isPaused = false;
		delete pauseEnt;
		pauseEnt = NULL;
	}
}

void GameScreen::screenShown()
{
  playerOne = new Ship(GamepadInputManager::sharedInstance()->playerOne(), this);
  
  for(int i = 0; i < 15; i++)
  {
	 entities.add(new Asteroid());
  }
  
  entities.add(playerOne);
}

void GameScreen::update(GfxWrapper* gfx)
{
	if(!isPaused)
	{
		entities.updateAll();
		entities.renderAll(gfx);
	}
	else
	{
		entities.renderAll(gfx);
		pauseEnt->update();
		pauseEnt->render(gfx);
	}
}

void GameScreen::setListener(ScreenListener* listener)
{
  this->listener = listener;
}

void GameScreen::shipDied(Ship* ship)
{
}

void GameScreen::shipFired(Ship* ship)
{
	printf("pew pew\n");
}

void GameScreen::shipRequestedPause(Ship* ship)
{
	isPaused = true;
	pauseEnt = new InGame(ship->getGamepad(), this);
}

void GameScreen::ingameContinueSelected()
{
	isPaused = false;
	delete pauseEnt;
	pauseEnt = NULL;
}

void GameScreen::ingameQuitSelected()
{
	listener->screenClosed(this, 0);
}
