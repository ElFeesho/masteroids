#ifndef __SCREENMANAGER_H__
#define __SCREENMANAGER_H__

#include <memory>

#include "screens/screen.h"
#include "screens/gamescreen.h"
#include "screens/gameoverscreen.h"
#include "screens/menuscreen.h"

class GfxWrapper;

class ScreenManager : public MenuScreenListener, public GameScreenListener, public GameOverScreenListener
{
public:
    ScreenManager();

	~ScreenManager();

    void menuScreenShouldExitGame() override;
    void menuScreenShouldShowGameScreen() override;

    void gameScreenShouldShowGameOverScreen() override;
    void gameScreenShouldShowMenu() override;

    void gameOverScreenShouldClose() override;

    void update(GfxWrapper &gfx);

private:
    Screen *activeScreen;
    MenuScreen menuScreen;
    GameScreen gameScreen;
    GameOverScreen gameOverScreen;

    void switchScreen(Screen &from, Screen &newScreen);
};

#endif
