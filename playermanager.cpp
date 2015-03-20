#include <math.h>
#include "playermanager.h"
#include "input/gamepadinputmanager.h"

#ifdef __WII__
#define M_PI        3.14159265358979323846264338327950288   /* pi             */
#define M_PI_2      1.57079632679489661923132169163975144   /* pi/2           */
#define M_PI_4      0.785398163397448309615660845819875721  /* pi/4           */
#endif

PlayerManager::PlayerManager(int playerCount, int lives, int maxBullets, std::function<void()> gameOver)
		: playingPlayers(playerCount), playerScores{0, 0, 0, 0},
		  bulletGenerators{BulletGenerator([]()
		  {
		  }), BulletGenerator([]()
		  {
		  }), BulletGenerator([]()
		  {
		  }), BulletGenerator([]()
		  {
		  })},
		  playerMovers{ShipMover(), ShipMover(), ShipMover(), ShipMover()},
		  playerScorePositions{Position(5, 5, 0), Position(635, 5, 0), Position(5, 440, 0), Position(635, 440, 0)},
		  playerColours{RGB::green, RGB::yellow, RGB::blue, RGB::purple},
		  livesRenderer(LivesRenderer()),
		  gameOverCallback(gameOver)
{
	if (playingPlayers == 1)
	{
		playerSpawnLocations[0] = Position(320, 240, -M_PI_2);
	}
	else if (playingPlayers == 2)
	{
		playerSpawnLocations[0] = Position(160, 240, 0);
		playerSpawnLocations[1] = Position(480, 240, -M_PI);
	}
	else if (playingPlayers == 3)
	{
		playerSpawnLocations[0] = Position(320, 120, M_PI_2);
		playerSpawnLocations[1] = Position(160, 320, -M_PI_4);
		playerSpawnLocations[2] = Position(480, 320, -M_PI_4 * 3);
	}
	else if (playingPlayers == 4)
	{
		playerSpawnLocations[0] = Position(160, 120, M_PI_4);
		playerSpawnLocations[1] = Position(480, 120, M_PI_4 * 3);
		playerSpawnLocations[2] = Position(160, 320, -M_PI_4);
		playerSpawnLocations[3] = Position(480, 320, -M_PI_4 * 3);
	}

	for (int i = 0; i < playingPlayers; i++)
	{
		playersLives[i] = lives;
		bulletGenerators[i] = BulletGenerator([&, i]()
		{
			if (playerBullets[i].size() < maxBullets)
			{
				Direction bulletDir = Direction(5.0f, players[i]->direction().Angle());
				playerBullets[i].add(bulletFactory.createBullet(playerColours[i], bulletDir, players[i]->position()));
			}
		});

		players[i] = shipFactory.createShip(playerColours[i], playerSpawnLocations[i]);
		players[i]->position().set(playerSpawnLocations[i].X(), playerSpawnLocations[i].Y(), playerSpawnLocations[i].Rotation());
		players[i]->direction().Angle(playerSpawnLocations[i].Rotation());
		players[i]->direction().Speed(0);
		directionControllers[i] = new DirectionController(GamepadInputManager::sharedInstance()->inputForPlayer(i), players[i]->direction());

		bulletGenerators[i].attachToButton(GamepadInputManager::sharedInstance()->inputForPlayer(i).fire());
		players[i]->setVisible(true);
	}
}

PlayerManager::PlayerManager() : playingPlayers(0), playerScores{0, 0, 0, 0},
											bulletGenerators{BulletGenerator([]()
											{
											}), BulletGenerator([]()
											{
											}), BulletGenerator([]()
											{
											}), BulletGenerator([]()
											{
											})},
											playerMovers{ShipMover(), ShipMover(), ShipMover(), ShipMover()},
											playerScorePositions{Position(5, 5, 0), Position(635, 5, 0), Position(5, 440, 0), Position(635, 440, 0)},
											playerColours{RGB::green, RGB::yellow, RGB::blue, RGB::purple},
											livesRenderer(LivesRenderer()),
											gameOverCallback([]()
											{
											})
{
}


void PlayerManager::checkPlayerBulletCollisions()
{
	for (int i = 0; i < playingPlayers; i++)
	{
		for (int j = 0; j < playingPlayers; j++)
		{
			if (i == j)
			{
				continue;
			}

			playerBullets[j].checkCollisions(*players[i], [&](Entity *hit)
			{
				killPlayer(i);
				playerBullets[j].removeEntity(hit);
			});
		}
	}
}

void PlayerManager::shutdown()
{
	for (int i = 0; i < playingPlayers; i++)
	{
		delete players[i];
		playersLives[i] = 0;
		playerMovers[i].reset();
		playerBullets[i].clear();
		playerScores[i] = 0;

		bulletGenerators[i].detachFromButton(GamepadInputManager::sharedInstance()->inputForPlayer(i).fire());
	}
}


void PlayerManager::updatePlayerScore(int player, int value)
{
	playerScores[player] += value;
}

EntityList &PlayerManager::bulletsForPlayer(int player)
{
	return playerBullets[player];
}

void PlayerManager::updatePlayer(int playerNumber, GfxWrapper *gfx)
{
	players[playerNumber]->update();
	players[playerNumber]->render(gfx);
	playerBullets[playerNumber].updateAll();
	playerBullets[playerNumber].renderAll(gfx);


	scoreRenderer.setScore(playerScores[playerNumber]);
	livesRenderer.setLives(playersLives[playerNumber]);
	TextAlignment alignment = playerNumber & 1 ? RIGHT : LEFT;
	scoreRenderer.setAlignment(alignment);
	livesRenderer.setAlignment(alignment);

	scoreRenderer.render(gfx, playerScorePositions[playerNumber], Shape::NONE, Direction::NONE, playerColours[playerNumber]);
	livesRenderer.render(gfx, playerScorePositions[playerNumber], Shape::NONE, Direction::NONE, playerColours[playerNumber]);
}


void PlayerManager::killPlayer(Entity * player)
{
	for (int i = 0; i < playingPlayers; i++)
	{
		if ((players[i]) == player)
		{
			killPlayer(i);
			break;
		}
	}
}

void PlayerManager::killPlayer(int playerNumber)
{
	players[playerNumber]->setVisible(false);
	playersLives[playerNumber]--;
	if (playersLives[playerNumber] > 0)
	{
		respawnShip(playerNumber);
		playerMovers[playerNumber].reset();
	}
	else
	{
		bool shouldGoToGameover = true;
		for (int i = 0; i < playingPlayers; i++)
		{
			shouldGoToGameover &= playersLives[i] == 0;
		}

		if (shouldGoToGameover)
		{
			GameTime::schedule(3000, [&]()
			{
				gameOverCallback();
			});
		}
	}
}

void PlayerManager::respawnShip(int playerNumber)
{
	GameTime::schedule(1500, [&, playerNumber]()
	{
		players[playerNumber]->position().X(playerSpawnLocations[playerNumber].X());
		players[playerNumber]->position().Y(playerSpawnLocations[playerNumber].Y());
		players[playerNumber]->position().Rotation(playerSpawnLocations[playerNumber].Rotation());
		players[playerNumber]->direction().Angle(playerSpawnLocations[playerNumber].Rotation());
		players[playerNumber]->direction().Speed(0);
		players[playerNumber]->setVisible(true);
		players[playerNumber]->mover()->reset();
	});
}

void PlayerManager::checkCollisionsWithPlayers(EntityList & entityList, std::function<void(Entity * , Entity * )> hitHandler)
{
	for (int i = 0; i<playingPlayers; i++)
	{
		if (players[i]->isVisible())
		{
			entityList.checkCollisions(*players[i], [&](Entity *hitEnt)
			{
				hitHandler(players[i], hitEnt);
			});
		}
	}
}
