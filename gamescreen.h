#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <renderers/livesrenderer.h>
#include "screen.h"
#include "entitylist.h"
#include "ship.h"
#include "ingame.h"
#include "debrisfountain.h"
#include "renderers/livesrenderer.h"
#include "renderers/scorerenderer.h"
#include "asteroidfactory.h"

class GameScreen : public Screen, public ShipListener, public InGameListener {
public:
    GameScreen();

    ~GameScreen();

    void screenHidden();

    void screenShown();

    void update(GfxWrapper *gfx);

    void setListener(ScreenListener *listener);

    void shipFired(Ship *ship);

    void shipRequestedPause(Ship *ship);

    void ingameContinueSelected();

    void ingameQuitSelected();

    void generateLevel();

private:
    AsteroidFactory asteroidFactory;
    ScreenListener *listener;
    EntityList asteroids;
    EntityList secondaryAsteroids;

    EntityList debrisEntities;
    DebrisFountain debrisFountain;
    InGame *pauseEnt;

    bool isPaused;

    Ship *players[4];
    ShipMover playerMovers[4];
    EntityList playerBullets[4];
    Position playerScorePositions[4];
    Position playerSpawnLocations[4];
    RGB playerColours[4];
    LivesRenderer livesRenderer;
    ScoreRenderer scoreRenderer;
    int playerScores[4];
    int playersLives[4];
    int level;

    void checkAsteroidCollisions(int playerNumber);

    void updatePlayers(GfxWrapper *gfx);

    void checkPlayerDeaths();

    void killPlayer(int playerNumber);

    void respawnShip(int playerNumber);

    void checkLevelComplete();

    void generateSecondaryAsteroids(Entity *hit);
};

#endif // GAMESCREEN_H
