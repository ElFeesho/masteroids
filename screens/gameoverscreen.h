#ifndef __GAMEOVERSCREEN_H__
#define __GAMEOVERSCREEN_H__

#include "screen.h"
#include "gameover.h"
#include <functional>

class GameOverScreenListener
{
public:
    virtual ~GameOverScreenListener() {}
    virtual void gameOverScreenShouldClose() = 0;
};

class GameOverScreen : public Screen
{
public:
    GameOverScreen(GameOverScreenListener &listener);

	~GameOverScreen();

    void update(Gfx &gfx) override;

	void screenShown() override;

	void screenHidden() override;

private:
    GameOverScreenListener &listener;
	GameOver gameOverEntity;
    std::function<void()> closeScreenHandler;
};

#endif

