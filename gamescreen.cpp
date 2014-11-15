#include "gamescreen.h"
#include "asteroid.h"
#include "ship.h"
#include "bullet.h"
#include "input/gamepadinputmanager.h"
#include <stdio.h>
#include "gfx/gfx.h"
#include "options.h"
#include <string>
#include <sstream>

using std::stringstream;

GameScreen::GameScreen() : isPaused(false), level(0), playerScores({0,0,0,0}), playerMovers({ShipMover(), ShipMover(), ShipMover(), ShipMover()})
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
  players[0] = new Ship(GamepadInputManager::sharedInstance()->playerOne(), this, playerMovers[0]);

  generateLevel();
}

void GameScreen::generateLevel()
{
	for(int i = 0; i < 7 + (level/2); i++)
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

		for(int i = 0; i<Options::players; i++)
		{
			players[i]->update();
			players[i]->render(gfx);
			playerBullets[i].updateAll();
			playerBullets[i].renderAll(gfx);
			
			checkAsteroidCollisions(i);
		}

		asteroids.updateAll();
		asteroids.renderAll(gfx);

		secondaryAsteroids.updateAll();
		secondaryAsteroids.renderAll(gfx);

		
// 		asteroids.checkCollisions(*playerOne, [&](Entity *hit){
// 			if(playerOne->isVisible())
// 			{
// 				debrisFountain.projectDebris(debrisEntities, Direction(3.5, playerOne->direction().Angle()), playerOne->position(), 1.3f, 6);
// 				//playerOne->setVisible(false);
// 								
// 				playerOne->position().X(640/4);
// 				playerOne->position().Y(480/4);
// 				
// 				playerOne->direction().Angle(0);
// 				playerOne->direction().Speed(0);
// 				playerOneMover.reset();
// 				
// 			}
// 		});
		
		if(asteroids.size() == 0 && secondaryAsteroids.size() == 0)
		{
			level++;
			generateLevel();
		}
	}
	else
	{
		asteroids.renderAll(gfx);
		pauseEnt->update();
		pauseEnt->render(gfx);
	}
	
	stringstream sstream;
	
	sstream << "SCORE " << playerScores[0];
	gfx->drawText(5,5,sstream.str(), RGB::green, LEFT);
}

void GameScreen::checkAsteroidCollisions(int playerNumber)
{
	asteroids.checkCollisions(playerBullets[playerNumber], [&](Entity* asteroid, Entity* bullet) {
		debrisFountain.projectDebris(debrisEntities, asteroid->direction(), asteroid->position(), 1.3f, 6);
		secondaryAsteroids.add(new Asteroid(10.0f, Position(asteroid->position())));
		secondaryAsteroids.add(new Asteroid(10.0f, Position(asteroid->position())));
		playerBullets[playerNumber].removeEntity(bullet);
		playerScores[playerNumber] += 10;
		asteroids.removeEntity(asteroid);
	});

	secondaryAsteroids.checkCollisions(playerBullets[playerNumber], [&](Entity* asteroid, Entity* bullet) {
		debrisFountain.projectDebris(debrisEntities, asteroid->direction(), asteroid->position(), 1.3f, 6);
		playerBullets[playerNumber].removeEntity(bullet);
		playerScores[playerNumber] += 25;
		secondaryAsteroids.removeEntity(asteroid);
	});
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
