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
#include "bulletfactory.h"
#include "directioncontroller.h"

#include "shipfactory.h"
#include "playermanager.h"

class GameScreenListener
{
public:
    virtual ~GameScreenListener() {}

    virtual void gameScreenShouldShowGameOverScreen() = 0;
    virtual void gameScreenShouldShowMenu() = 0;
};

class GameScreen : public Screen, public PauseDialogListener
{
public:
    GameScreen(GameScreenListener &listener);

	void screenHidden();

	void screenShown();

    void update(Gfx &gfx);

	void ingameContinueSelected();

	void ingameQuitSelected();

	void generateLevel();
private:

	AsteroidFactory asteroidFactory;
    GameScreenListener &listener;
	EntityList asteroids;
    PauseDialog pauseEnt;

    PlayerManager playerManager{0, 3, [](){}};

	bool isPaused { false };
	int level { 0 };

    std::function<void()> pauseHandler;
};

