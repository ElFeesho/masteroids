#include <iostream>
#include "gamescreen.h"

using std::stringstream;

GameScreen::GameScreen(GameScreenListener &screenListener) :
        ship(std::unique_ptr<Actor>(shipFactory.createShip(RGB::PURPLE, Position(400, 200, 10)))),
        listener(screenListener),
        pauseEnt(GamepadInputManager::sharedInstance().inputForPlayer(0), this),
        isPaused(false),
        level(0),
        pauseHandler([&](){
            isPaused = true;
            pauseEnt.shown();
        })
{
}

void GameScreen::screenHidden()
{
	GamepadInputManager::sharedInstance().inputForPlayer(0).pause().removeUpHandler();
	asteroids.clear();

    isPaused = false;
    level = 1;
}

void GameScreen::screenShown()
{
    GamepadInputManager::sharedInstance().inputForPlayer(0).pause().addUpHandler(pauseHandler);
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
		asteroids.updateAll();
		asteroids.renderAll(gfx);
        ship->update();
        ship->render(gfx);
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

