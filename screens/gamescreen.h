#pragma once

#include <memory>
#include <vector>

#include "renderers/livesrenderer.h"
#include "input/gamepadinputmanager.h"
#include "screen.h"
#include "entitylist.h"
#include "pausedialog.h"
#include "debrisfountain.h"
#include "renderers/livesrenderer.h"
#include "renderers/scorerenderer.h"
#include "asteroidfactory.h"
#include "directioncontroller.h"

#include "shipfactory.h"

class GameScreenListener {
public:
    virtual ~GameScreenListener() { }

    virtual void gameScreenShouldShowGameOverScreen() = 0;

    virtual void gameScreenShouldShowMenu() = 0;
};

class GameScreen : public Screen, public PauseDialogListener {
public:
    GameScreen(GameScreenListener &listener);

    void generateLevel();

    void screenHidden() override ;
    void screenShown() override ;
    void update(Gfx &gfx) override;
    void ingameContinueSelected() override;
    void ingameQuitSelected() override;

private:
    ShipFactory shipFactory;
    std::unique_ptr<Actor> ship;
    AsteroidFactory asteroidFactory;
    GameScreenListener &listener;
    EntityList asteroids;
    PauseDialog pauseEnt;

    bool isPaused;
    int level;

    std::function<void()> pauseHandler;
};

