#ifndef __GAMEOVERSCREEN_H__
#define __GAMEOVERSCREEN_H__

#include "input/gamepad.h"
#include "screen.h"
#include "gameover.h"
#include <functional>

class GameOverScreenListener {
public:
    virtual ~GameOverScreenListener() { }

    virtual void gameOverScreenShouldClose() = 0;
};

class GameOverScreen : public Screen {

    class CloseScreenHandler : public ButtonCommand
    {
    public:
        CloseScreenHandler(GameOverScreenListener &listener);
        virtual void buttonAction() override;
    private:
        GameOverScreenListener &listener;
    };
public:
    GameOverScreen(GameOverScreenListener &listener);

    ~GameOverScreen();

    void update(Gfx &gfx) override;

    void screenShown() override;

    void screenHidden() override;

private:
    GameOverScreenListener &listener;
    GameOver gameOverEntity;
    CloseScreenHandler closeScreenHandler;
};

#endif

