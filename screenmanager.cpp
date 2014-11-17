#include "screenmanager.h"
#include "menuscreen.h"
#include "gamescreen.h"
#include "gameoverscreen.h"

ScreenManager::ScreenManager()
        : menuScreen(new MenuScreen()), gameScreen(new GameScreen()), gameOverScreen(new GameOverScreen()) {
    menuScreen->setListener(this);
    gameScreen->setListener(this);
    gameOverScreen->setListener(this);

    activeScreen = menuScreen;
    menuScreen->screenShown();
}

ScreenManager::~ScreenManager() {

}

void ScreenManager::update(GfxWrapper *gfx) {
    activeScreen->update(gfx);
}

void ScreenManager::switchScreen(Screen *newScreen) {
    Screen *oldScreen = activeScreen;
    activeScreen = newScreen;
    oldScreen->screenHidden();
    activeScreen->screenShown();
}

void ScreenManager::screenClosed(Screen *screen, int reason) {
    if (screen == menuScreen) {
        if (reason == 1) {
            switchScreen(gameScreen);
        }
    }
    else if (screen == gameScreen) {
        if (reason == 0) {
            switchScreen(menuScreen);
        }
        else if (reason == 1) {
            switchScreen(gameOverScreen);
        }
    }
}