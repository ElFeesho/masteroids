#include "gamescreen.h"
#include "asteroid.h"
#include "ship.h"
#include "bullet.h"
#include "input/gamepadinputmanager.h"
#include <stdio.h>

GameScreen::GameScreen() : isPaused(false)
{
}

GameScreen::~GameScreen()
{

}

void GameScreen::screenHidden()
{
	asteroids.clear();
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
	 asteroids.add(new Asteroid());
  }
}

void GameScreen::update(GfxWrapper* gfx)
{
	if(!isPaused)
	{
		debrisEntities.updateAll();
		debrisEntities.renderAll(gfx);

		playerOne->update();
		playerOne->render(gfx);

		playerBullets[0].updateAll();
		playerBullets[0].renderAll(gfx);

		asteroids.updateAll();
		asteroids.renderAll(gfx);

		secondaryAsteroids.updateAll();
		secondaryAsteroids.renderAll(gfx);

		asteroids.checkCollisions(playerBullets[0], [&](Entity* asteroid, Entity* bullet) {
			debrisFountain.projectDebris(debrisEntities, asteroid->direction(), asteroid->position(), 1.3f, 6);
			secondaryAsteroids.add(new Asteroid(10.0f, Position(asteroid->position())));
			secondaryAsteroids.add(new Asteroid(10.0f, Position(asteroid->position())));
			playerBullets[0].removeEntity(bullet);
			asteroids.removeEntity(asteroid);
		});

		secondaryAsteroids.checkCollisions(playerBullets[0], [&](Entity* asteroid, Entity* bullet) {
			debrisFountain.projectDebris(debrisEntities, asteroid->direction(), asteroid->position(), 1.3f, 6);
			playerBullets[0].removeEntity(bullet);
			secondaryAsteroids.removeEntity(asteroid);
		});
	}
	else
	{
		asteroids.renderAll(gfx);
		playerBullets[0].renderAll(gfx);
		playerOne->render(gfx);
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
	playerBullets[0].add(new Bullet(ship, ship->direction()));
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
