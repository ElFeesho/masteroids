#pragma once

#include <functional>
#include "gfx/gfx.h"
#include "entity.h"
#include "shipfactory.h"
#include "bulletfactory.h"
#include "entitylist.h"
#include "renderers/scorerenderer.h"
#include "renderers/livesrenderer.h"
#include "directioncontroller.h"

#include <iostream>
class MemWatch {
public:
    MemWatch() = default;
    MemWatch(MemWatch&) = default;
    MemWatch(MemWatch&&) = default;
    MemWatch &operator=(MemWatch&) = default;
    MemWatch &operator=(MemWatch&&) = default;
    ~MemWatch() {
        std::cout << "DTORRED" << std::endl;
    }
};

class PlayerManager
{
public:
    PlayerManager(int playerNumber, int lives, std::function<void()> gameOver);

    void killPlayer();

	void respawnShip();

    void updatePlayer(Gfx &gfx);

    EntityList & bulletsForPlayer();

    void updatePlayerScore(int value);

	void checkCollisionsWithPlayers(EntityList &entityList, std::function<void(Entity * , Entity * )> hitHandler);

    void checkPlayerBulletCollisions(PlayerManager &);

	void shutdown();

    void reset();

private:
    int playerNumber;
	BulletFactory bulletFactory;

    DirectionController *directionController;

    Actor *player;

    ShipFactory shipFactory;

    Position playerSpawnLocation{ 0, 0, 0 };

    EntityList playerBullets;

    int playerScore;
    int playersLives;

	LivesRenderer livesRenderer;
	ScoreRenderer scoreRenderer;

	std::function<void()> gameOverCallback;
    MemWatch w;
};
