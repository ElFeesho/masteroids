#include <iostream>
#include "gamescreen.h"
#include "options.h"

using std::stringstream;

GameScreen::GameScreen(GameScreenListener &screenListener) :
        listener(screenListener),
        pauseEnt(GamepadInputManager::sharedInstance().inputForPlayer(0), this),
        isPaused(false),
        level(0),
        pauseHandler(new std::function<void()>([&](){
            isPaused = true;
            pauseEnt.shown();
        }))
{

}

GameScreen::~GameScreen()
{

}

void GameScreen::screenHidden()
{
    GamepadInputManager::sharedInstance().inputForPlayer(0).pause().removeUpHandler(pauseHandler.get());
	asteroids.clear();
	secondaryAsteroids.clear();
	debrisEntities.clear();
    isPaused = false;
    playerManagers.clear();
}

void GameScreen::screenShown()
{
    GamepadInputManager::sharedInstance().inputForPlayer(0).pause().addUpHandler(pauseHandler.get());

    playerManagers.emplace_back(std::unique_ptr<PlayerManager>(new PlayerManager(Options::players, Options::lives, Options::max_bullets, [this](){
        listener.gameScreenShouldShowGameOverScreen();
    })));

	generateLevel();
}

void GameScreen::generateLevel()
{
	for (int i = 0; i < 7 + (level / 2); i++)
	{
		asteroids.add(asteroidFactory.createAsteroid(25.0f));
	}
}

void GameScreen::update(Gfx &gfx)
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
        pauseEnt.update();
        pauseEnt.render(gfx);
	}

}

void GameScreen::checkPlayerDeaths()
{
    for(auto &playerManager : playerManagers)
    {
        playerManager.get()->checkCollisionsWithPlayers(asteroids, [&](Entity *, Entity *hitAsteroid){
            playerManager.get()->killPlayer();
            asteroids.removeEntity(hitAsteroid);
            generateSecondaryAsteroids(hitAsteroid);
        });
    }

    for(auto &playerManager : playerManagers)
    {
        playerManager.get()->checkCollisionsWithPlayers(secondaryAsteroids, [&](Entity *, Entity *hitAsteroid){
            playerManager.get()->killPlayer();
            secondaryAsteroids.removeEntity(hitAsteroid);
            checkLevelComplete();
        });
    }

	if(Options::team_kill)
	{
        for(auto &playerManager : playerManagers)
        {
            for(auto &playerManagerCollider : playerManagers)
            {
                playerManager.get()->checkPlayerBulletCollisions(*playerManagerCollider.get());
            }
        }
	}
}

void GameScreen::generateSecondaryAsteroids(Entity *hit)
{
	secondaryAsteroids.add(asteroidFactory.createAsteroid(10.0f, hit->position()));
	secondaryAsteroids.add(asteroidFactory.createAsteroid(10.0f, hit->position()));
}

//void GameScreen::killPlayer(int playerNumber)
//{
//	//debrisFountain.projectDebris(debrisEntities, Direction(0.5f, players[playerNumber]->direction().Angle()), players[playerNumber]->position(), 1.3f, 12, playerColours[playerNumber]);
//	playerManager.killPlayer(playerNumber);
//}

void GameScreen::updatePlayers(Gfx &gfx)
{
    for(auto &playerManager : playerManagers)
    {
        playerManager.get()->updatePlayer(gfx);
        checkAsteroidCollisions(playerManager.get());
    }
}


void GameScreen::checkAsteroidCollisions(PlayerManager *playerManager)
{
    asteroids.checkCollisions(playerManager->bulletsForPlayer(), [&](Entity *asteroid, Entity *bullet)
	{
		debrisFountain.projectDebris(debrisEntities, asteroid->direction(), asteroid->position(), 1.3f, 6, RGB::white);
		generateSecondaryAsteroids(asteroid);
        playerManager->bulletsForPlayer().removeEntity(bullet);
        playerManager->updatePlayerScore(10);
		asteroids.removeEntity(asteroid);
	});

    secondaryAsteroids.checkCollisions(playerManager->bulletsForPlayer(), [&](Entity *asteroid, Entity *bullet)
	{
		debrisFountain.projectDebris(debrisEntities, asteroid->direction(), asteroid->position(), 1.3f, 6, RGB::white);
        playerManager->bulletsForPlayer().removeEntity(bullet);
        playerManager->updatePlayerScore(25);
		secondaryAsteroids.removeEntity(asteroid);
		checkLevelComplete();
	});
}

void GameScreen::ingameContinueSelected()
{
    isPaused = false;
}

void GameScreen::ingameQuitSelected()
{
    listener.gameScreenShouldShowMenu();
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
