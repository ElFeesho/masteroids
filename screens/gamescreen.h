#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <renderers/livesrenderer.h>
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

class GameScreen : public Screen, public PauseDialogListener
{
public:
	GameScreen();

	~GameScreen();

	void screenHidden();

	void screenShown();

	void update(GfxWrapper *gfx);

	void setListener(ScreenListener *listener);

	void ingameContinueSelected();

	void ingameQuitSelected();

	void generateLevel();

private:
	AsteroidFactory asteroidFactory;
	BulletFactory bulletFactory;
	ShipFactory shipFactory;
	ScreenListener *listener;
	EntityList asteroids;
	EntityList secondaryAsteroids;
	EntityList debrisEntities;

	DebrisFountain debrisFountain;
	PauseDialog *pauseEnt;

	bool isPaused;

	Actor *players[4];
	ShipMover playerMovers[4];
	EntityList playerBullets[4];
	Position playerScorePositions[4];
	Position playerSpawnLocations[4];
	BulletGenerator bulletGenerators[4];
	RGB playerColours[4];
	LivesRenderer livesRenderer;
	ScoreRenderer scoreRenderer;
	int playerScores[4];
	int playersLives[4];
	int level;

	DirectionController *directionControllers[4];

	void checkAsteroidCollisions(int playerNumber);

	void updatePlayers(GfxWrapper *gfx);

	void checkPlayerDeaths();

	void killPlayer(int playerNumber);

	void respawnShip(int playerNumber);

	void checkLevelComplete();

	void generateSecondaryAsteroids(Entity *hit);
};

#endif // GAMESCREEN_H
