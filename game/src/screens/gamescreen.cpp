#include <iostream>
#include "gamescreen.h"
#include "menu/options.h"

using std::stringstream;

GameScreen::GameScreen(GameScreenListener &screenListener) :
        listener(screenListener),
        pauseEnt(GamepadInputManager::sharedInstance().inputForPlayer(0), this),
        pauseHandler([&](){
            isPaused = true;
            pauseEnt.shown();
        })
{

}

void GameScreen::screenHidden()
{
    GamepadInputManager::sharedInstance().inputForPlayer(0).pause().removeUpHandler(&pauseHandler);
	asteroids.clear();

    isPaused = false;
    level = 0;

    playerManager.shutdown();
}

void GameScreen::screenShown()
{
    GamepadInputManager::sharedInstance().inputForPlayer(0).pause().addUpHandler(&pauseHandler);
	generateLevel();

    playerManager.reset();
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
		asteroids.updateAll();
		debris.updateAll();
        debris.renderAll(gfx);
        asteroids.renderAll(gfx);

        playerManager.updatePlayer(gfx);

        playerManager.bulletsForPlayer().checkCollisions(asteroids, [&](Entity *bullet, Entity *asteroid) {

            if (asteroid->shape().Radius()>10.f) {
                asteroids.add(asteroidFactory.createAsteroid(asteroid->shape().Radius()-8.f, asteroid->position()));
                asteroids.add(asteroidFactory.createAsteroid(asteroid->shape().Radius()-8.f, asteroid->position()));
                asteroids.add(asteroidFactory.createAsteroid(asteroid->shape().Radius()-8.f, asteroid->position()));
                asteroids.add(asteroidFactory.createAsteroid(asteroid->shape().Radius()-8.f, asteroid->position()));
            }
            
            debrisFountain.projectDebris(debris, asteroid->direction(), asteroid->position(), M_PI_2/2.f, 8, RGB::WHITE, asteroid->shape().Radius()/2.f);

            playerManager.updatePlayerScore(100 - asteroid->shape().Radius());

            asteroids.removeEntity(asteroid);

            playerManager.bulletsForPlayer().removeEntity(bullet);
        });

        playerManager.checkCollisionsWithPlayers(asteroids, [&](Entity *, Entity *asteroid) {
            playerManager.killPlayer();
            if (asteroid->shape().Radius()>10.f) {
                asteroids.add(asteroidFactory.createAsteroid(asteroid->shape().Radius()-8.f, asteroid->position()));
                asteroids.add(asteroidFactory.createAsteroid(asteroid->shape().Radius()-8.f, asteroid->position()));
                asteroids.add(asteroidFactory.createAsteroid(asteroid->shape().Radius()-8.f, asteroid->position()));
                asteroids.add(asteroidFactory.createAsteroid(asteroid->shape().Radius()-8.f, asteroid->position()));
            }

            debrisFountain.projectDebris(debris, asteroid->direction(), asteroid->position(), M_PI_2/2.f, 8, RGB::WHITE, asteroid->shape().Radius()/2.f);

            asteroids.removeEntity(asteroid);
        });
	}
	else
	{
		asteroids.renderAll(gfx);
        pauseEnt.update();
        pauseEnt.render(gfx);

	}
}

void GameScreen::ingameContinueSelected()
{
    isPaused = false;
}

void GameScreen::ingameQuitSelected()
{
    pauseEnt.reset();
    listener.gameScreenShouldShowMenu();
}

