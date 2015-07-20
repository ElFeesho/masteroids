#include <iostream>
#include "gamescreen.h"
#include "options.h"

using std::stringstream;

static std::function<void()> pauseHandler;

GameScreen::GameScreen() :
		isPaused(false),
		level(0),
		pauseEnt(NULL)
{
	pauseHandler = [&](){
		isPaused = true;
        pauseEnt = new PauseDialog(GamepadInputManager::sharedInstance().inputForPlayer(0), this);
	};
}

GameScreen::~GameScreen()
{

}

void GameScreen::screenHidden()
{
    GamepadInputManager::sharedInstance().inputForPlayer(0).pause().removeUpHandler(&pauseHandler);
	asteroids.clear();
	secondaryAsteroids.clear();
	debrisEntities.clear();
	if (pauseEnt != NULL)
	{
		isPaused = false;
		delete pauseEnt;
		pauseEnt = NULL;
	}

	playerManager.shutdown();
}

void GameScreen::screenShown()
{
	playerManager = PlayerManager(Options::players, Options::lives, Options::max_bullets, [this](){
		this->listener->screenClosed(this, 0);
	});
    GamepadInputManager::sharedInstance().inputForPlayer(0).pause().addUpHandler(&pauseHandler);

	generateLevel();
}

void GameScreen::generateLevel()
{
	for (int i = 0; i < 7 + (level / 2); i++)
	{
		asteroids.add(asteroidFactory.createAsteroid(25.0f));
	}
}

void GameScreen::update(GfxWrapper *gfx)
{
	if (!isPaused)
	{
		debrisEntities.updateAll();
		debrisEntities.renderAll(gfx);

		updatePlayers(gfx);

		asteroids.updateAll();
		asteroids.renderAll(gfx);

		secondaryAsteroids.updateAll();
		secondaryAsteroids.renderAll(gfx);

		checkPlayerDeaths();
	}
	else
	{
		asteroids.renderAll(gfx);
		pauseEnt->update();
		pauseEnt->render(gfx);
	}

}

void GameScreen::checkPlayerDeaths()
{
	playerManager.checkCollisionsWithPlayers(asteroids, [&](Entity *hitPlayer, Entity *hitAsteroid){
		playerManager.killPlayer(hitPlayer);
		asteroids.removeEntity(hitAsteroid);
		generateSecondaryAsteroids(hitAsteroid);
	});

	playerManager.checkCollisionsWithPlayers(secondaryAsteroids, [&](Entity *hitPlayer, Entity *hitAsteroid){
		playerManager.killPlayer(hitPlayer);
		secondaryAsteroids.removeEntity(hitAsteroid);
		checkLevelComplete();
	});

	if(Options::team_kill)
	{
		playerManager.checkPlayerBulletCollisions();
	}
}

void GameScreen::generateSecondaryAsteroids(Entity *hit)
{
	secondaryAsteroids.add(asteroidFactory.createAsteroid(10.0f, hit->position()));
	secondaryAsteroids.add(asteroidFactory.createAsteroid(10.0f, hit->position()));
}

void GameScreen::killPlayer(int playerNumber)
{
	//debrisFountain.projectDebris(debrisEntities, Direction(0.5f, players[playerNumber]->direction().Angle()), players[playerNumber]->position(), 1.3f, 12, playerColours[playerNumber]);
	playerManager.killPlayer(playerNumber);
}

void GameScreen::updatePlayers(GfxWrapper *gfx)
{
	for (int i = 0; i < Options::players; i++)
	{
		playerManager.updatePlayer(i, gfx);
		checkAsteroidCollisions(i);
	}
}


void GameScreen::checkAsteroidCollisions(int playerNumber)
{
	asteroids.checkCollisions(playerManager.bulletsForPlayer(playerNumber), [&](Entity *asteroid, Entity *bullet)
	{
		debrisFountain.projectDebris(debrisEntities, asteroid->direction(), asteroid->position(), 1.3f, 6, RGB::white);
		generateSecondaryAsteroids(asteroid);
		playerManager.bulletsForPlayer(playerNumber).removeEntity(bullet);
		playerManager.updatePlayerScore(playerNumber, 10);
		asteroids.removeEntity(asteroid);
	});

	secondaryAsteroids.checkCollisions(playerManager.bulletsForPlayer(playerNumber), [&](Entity *asteroid, Entity *bullet)
	{
		debrisFountain.projectDebris(debrisEntities, asteroid->direction(), asteroid->position(), 1.3f, 6, RGB::white);
		playerManager.bulletsForPlayer(playerNumber).removeEntity(bullet);
		playerManager.updatePlayerScore(playerNumber, 25);
		secondaryAsteroids.removeEntity(asteroid);
		checkLevelComplete();
	});
}


void GameScreen::setListener(ScreenListener *listener)
{
	this->listener = listener;
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

void GameScreen::checkLevelComplete()
{
	if (asteroids.size() == 0 && secondaryAsteroids.size() == 0)
	{
		GameTime::schedule(1500, [&]()
		{
			level++;
			generateLevel();
		});
	}
}
