#ifndef GAMESCREEN_H
#define GAMESCREEN_H

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



class GameScreen : public Screen, public PauseDialogListener
{
public:
	GameScreen();

	~GameScreen();

	void screenHidden();

	void screenShown();

    void update(GfxWrapper &gfx);

	void setListener(ScreenListener *listener);

	void ingameContinueSelected();

	void ingameQuitSelected();

	void generateLevel();

private:
	PlayerManager playerManager;

	AsteroidFactory asteroidFactory;

	ScreenListener *listener;
	EntityList asteroids;
	EntityList secondaryAsteroids;
	EntityList debrisEntities;

	DebrisFountain debrisFountain;
	PauseDialog *pauseEnt;

	bool isPaused;
	int level;

	void checkAsteroidCollisions(int playerNumber);

    void updatePlayers(GfxWrapper &gfx);

	void checkPlayerDeaths();

	void killPlayer(int playerNumber);

	void checkLevelComplete();

	void generateSecondaryAsteroids(Entity *hit);
};

#endif // GAMESCREEN_H
