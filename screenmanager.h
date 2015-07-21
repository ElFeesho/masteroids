#ifndef __SCREENMANAGER_H__
#define __SCREENMANAGER_H__

#include <memory>

#include "screens/screen.h"
#include "screens/gamescreen.h"
#include "screens/gameoverscreen.h"
#include "screens/menuscreen.h"

class GfxWrapper;

class ScreenManager : public MenuScreenListener
{
public:
    ScreenManager();

	~ScreenManager();

    void menuScreenShouldExitGame() override;
    void menuScreenShouldShowGameScreen() override;


    void update(GfxWrapper &gfx);

private:
    int gameMode { 0 };
    Screen *activeScreen;
    MenuScreen menuScreen;
    GameScreen gameScreen;
    GameOverScreen gameOverScreen;

    void switchScreen(Screen &from, Screen &newScreen);
};

#endif
