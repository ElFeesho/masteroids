#include <iostream>
#include "gamescreen.h"
#include "menu/options.h"

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

    isPaused = false;
    level = 1;
}

void GameScreen::screenShown()
{
    GamepadInputManager::sharedInstance().inputForPlayer(0).pause().addUpHandler(pauseHandler.get());
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

