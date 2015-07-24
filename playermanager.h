#ifndef __PLAYERMANAGER_H__
#define __PLAYERMANAGER_H__

#include <functional>
#include "gfx/gfx.h"
#include "entity.h"
#include "shipfactory.h"
#include "bulletfactory.h"
#include "bulletgenerator.h"
#include "entitylist.h"
#include "renderers/scorerenderer.h"
#include "renderers/livesrenderer.h"
#include "directioncontroller.h"

class PlayerManager
{
public:
    PlayerManager(PlayerManager &&) = default;

    PlayerManager(int playerNumber, int lives, int maxBullets, std::function<void()> gameOver);
    ~PlayerManager();

    void killPlayer();

	void killPlayer(Entity *player);

    void respawnShip();

    void updatePlayer(GfxWrapper &gfx);

    EntityList & bulletsForPlayer();

    void updatePlayerScore(int value);

	void checkCollisionsWithPlayers(EntityList &entityList, std::function<void(Entity * , Entity * )> hitHandler);

    void checkPlayerBulletCollisions(PlayerManager &);

	void shutdown();

private:
    int playerNumber;
	BulletFactory bulletFactory;

    DirectionController *directionController;
	int playingPlayers;

    Actor *player;

    ShipFactory shipFactory;

    Position playerSpawnLocation;

    EntityList playerBullets;

    int playerScore;
    int playersLives;
	Position playerScorePositions[4];

	LivesRenderer livesRenderer;
	ScoreRenderer scoreRenderer;

	std::function<void()> gameOverCallback;
};


#endif
