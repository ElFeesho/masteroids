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
#include "bulletgenerator.h"
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

	~GameScreen();

	void screenHidden();

	void screenShown();

    void update(GfxWrapper &gfx);

	void ingameContinueSelected();

	void ingameQuitSelected();

	void generateLevel();

private:
    std::vector<std::unique_ptr<PlayerManager>> playerManagers;

	AsteroidFactory asteroidFactory;

    GameScreenListener &listener;
	EntityList asteroids;
	EntityList secondaryAsteroids;
	EntityList debrisEntities;

	DebrisFountain debrisFountain;
    PauseDialog pauseEnt;

	bool isPaused;
	int level;

    void checkAsteroidCollisions(PlayerManager *playerManager);
    void updatePlayers(GfxWrapper &gfx);
    void checkPlayerDeaths();
	void checkLevelComplete();
	void generateSecondaryAsteroids(Entity *hit);
};

