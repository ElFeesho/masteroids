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
	PlayerManager();

	PlayerManager(int playerCount, int lives, int maxBullets, std::function<void()> gameOver);

	void killPlayer(int playerNumber);

	void killPlayer(Entity *player);

	void respawnShip(int playerNumber);

    void updatePlayer(int playerNumber, GfxWrapper &gfx);

	EntityList & bulletsForPlayer(int player);

	void updatePlayerScore(int player, int value);

	void checkCollisionsWithPlayers(EntityList &entityList, std::function<void(Entity * , Entity * )> hitHandler);

	void checkPlayerBulletCollisions();

	void shutdown();

private:
	BulletFactory bulletFactory;

	DirectionController *directionControllers[4];
	int playingPlayers;
	Actor *players[4];
	ShipMover playerMovers[4];
	EntityList playerBullets[4];
	ShipFactory shipFactory;
	Position playerSpawnLocations[4];
	BulletGenerator *bulletGenerators[4];
	RGB playerColours[4];
	int playerScores[4];
	int playersLives[4];
	Position playerScorePositions[4];

	LivesRenderer livesRenderer;
	ScoreRenderer scoreRenderer;

	std::function<void()> gameOverCallback;
};


#endif
