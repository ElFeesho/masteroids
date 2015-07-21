#include "screenmanager.h"
#include "screens/menuscreen.h"
#include "screens/gamescreen.h"
#include "screens/gameoverscreen.h"

ScreenManager::ScreenManager() : menuScreen(*this), gameScreen(), gameOverScreen()
{
    menuScreen.screenShown();
}

ScreenManager::~ScreenManager() {}

void ScreenManager::update(GfxWrapper &gfx)
{
    if (gameMode == 0)
    {
        menuScreen.update(gfx);
    }
    else if(gameMode == 1)
    {
        gameScreen.update(gfx);
    }
    else if(gameMode == 2)
    {
        gameOverScreen.update(gfx);
    }
}

void ScreenManager::switchScreen(Screen &oldScreen, Screen &newScreen)
{
    oldScreen.screenHidden();
    newScreen.screenShown();
}

void ScreenManager::menuScreenShouldShowGameScreen()
{
    switchScreen(menuScreen, gameScreen);
    gameMode = 1;
}

void ScreenManager::menuScreenShouldExitGame()
{
    // ...
}
