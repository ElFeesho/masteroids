#include "screenmanager.h"
#include "screens/menuscreen.h"
#include "screens/gamescreen.h"
#include "screens/gameoverscreen.h"

ScreenManager::ScreenManager() : menuScreen(*this), gameScreen(*this), gameOverScreen(*this)
{
    menuScreen.screenShown();
    activeScreen = &menuScreen;
}

bool ScreenManager::update(Gfx &gfx)
{
    activeScreen->update(gfx);
    return shouldRun;
}

void ScreenManager::switchScreen(Screen &oldScreen, Screen &newScreen)
{
    oldScreen.screenHidden();
    newScreen.screenShown();
    activeScreen = &newScreen;
}

void ScreenManager::menuScreenShouldShowGameScreen()
{
    switchScreen(menuScreen, gameScreen);
}

void ScreenManager::gameScreenShouldShowGameOverScreen()
{
    switchScreen(gameScreen, gameOverScreen);
}

void ScreenManager::gameScreenShouldShowMenu()
{
    switchScreen(gameScreen, menuScreen);
}

void ScreenManager::gameOverScreenShouldClose()
{
    switchScreen(gameOverScreen, menuScreen);
}

void ScreenManager::menuScreenShouldExitGame()
{
    shouldRun = false;
}
