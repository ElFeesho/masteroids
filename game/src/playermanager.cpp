#include <math.h>
#include "playermanager.h"
#include "input/gamepadinputmanager.h"
#include "menu/options.h"

#ifdef __WII__
#define M_PI        3.14159265358979323846264338327950288   /* pi             */
#define M_PI_2      1.57079632679489661923132169163975144   /* pi/2           */
#define M_PI_4      0.785398163397448309615660845819875721  /* pi/4           */
#endif

static RGB playerColours[] = {RGB::GREEN, RGB::YELLOW, RGB::BLUE, RGB::PURPLE};
static Position playerScorePositions[] = {Position(5, 5, 0), Position(635, 5, 0), Position(5, 440, 0),
                                          Position(635, 440, 0)};

static std::function<void()> *fireHandler;

PlayerManager::PlayerManager(int nplayerNumber, int lives, std::function<void()> gameOver)
        : playerNumber{nplayerNumber},
          playerScore{0},
          playersLives{lives},
          livesRenderer(),
          gameOverCallback(gameOver) {
    if (Options::players == 1) {
        playerSpawnLocation = Position(320, 240, -M_PI_2);
    } else if (Options::players == 2) {
        if (playerNumber == 1) {
            playerSpawnLocation = Position(160, 240, 0);
        } else {
            playerSpawnLocation = Position(480, 240, -M_PI);
        }
    } else if (Options::players == 3) {
        if (playerNumber == 1) {
            playerSpawnLocation = Position(320, 120, M_PI_2);
        } else if (playerNumber == 2) {
            playerSpawnLocation = Position(160, 320, -M_PI_4);
        } else {
            playerSpawnLocation = Position(480, 320, -M_PI_4 * 3);
        }
    } else if (Options::players == 4) {
        if (playerNumber == 1) {
            playerSpawnLocation = Position(160, 120, M_PI_4);
        } else if (playerNumber == 2) {
            playerSpawnLocation = Position(480, 120, M_PI_4 * 3);
        } else if (playerNumber == 3) {
            playerSpawnLocation = Position(160, 320, -M_PI_4);
        } else {
            playerSpawnLocation = Position(480, 320, -M_PI_4 * 3);
        }
    }

    playersLives = lives;

    player = shipFactory.createShip(playerColours[playerNumber - 1], playerSpawnLocation);
    directionController = new DirectionController();
    directionController->control(GamepadInputManager::sharedInstance().inputForPlayer(playerNumber - 1),
                                 player->direction());

    fireHandler = new std::function<void()>([&]() {
        if (playerBullets.size() < Options::max_bullets && player->isVisible()) {
            Direction bulletDir(5.0f, player->direction().Angle());
            playerBullets.add(bulletFactory.createBullet(RGB::GREEN, bulletDir, player->position()));
        }
    });

    GamepadInputManager::sharedInstance().inputForPlayer(0).fire().addDownHandler(fireHandler);
}

void PlayerManager::checkPlayerBulletCollisions(PlayerManager &playerManager) {
    playerManager.bulletsForPlayer().checkCollisions(*player, [&](Entity *hit) {
        killPlayer();
        playerManager.bulletsForPlayer().removeEntity(hit);
    });
}

void PlayerManager::reset() {
    for (int i = 0; i < Options::players; i++) {
        playersLives = 3;
        playerBullets.clear();
        playerScore = 0;

        player->position().X(playerSpawnLocation.X());
        player->position().Y(playerSpawnLocation.Y());
        player->position().Rotation(playerSpawnLocation.Rotation());
        player->direction().Angle(playerSpawnLocation.Rotation());
        player->direction().Speed(0);
        player->setVisible(true);
        player->mover().reset();

        GamepadInputManager::sharedInstance().inputForPlayer(0).fire().addDownHandler(fireHandler);
    }
}

void PlayerManager::shutdown() {
    for (int i = 0; i < Options::players; i++) {
        playersLives = 0;
        playerBullets.clear();
        playerScore = 0;

        GamepadInputManager::sharedInstance().inputForPlayer(0).fire().removeDownHandler(fireHandler);
    }
}

void PlayerManager::updatePlayerScore(int value) {
    playerScore += value;
}

EntityList &PlayerManager::bulletsForPlayer() {
    return playerBullets;
}

void PlayerManager::updatePlayer(Gfx &gfx) {
    player->update();
    player->render(gfx);
    playerBullets.updateAll();
    playerBullets.renderAll(gfx);

    scoreRenderer.setScore(playerScore);
    livesRenderer.setLives(playersLives);
    TextAlignment alignment = playerNumber & 1 ? TextAlignment::RIGHT : TextAlignment::LEFT;
    scoreRenderer.setAlignment(alignment);
    livesRenderer.setAlignment(alignment);

    scoreRenderer.render(gfx, playerScorePositions[playerNumber - 1], Shape::NONE, Direction::NONE, RGB::GREEN);
    livesRenderer.render(gfx, playerScorePositions[playerNumber - 1], Shape::NONE, Direction::NONE, RGB::GREEN);
}

void PlayerManager::killPlayer() {
    player->setVisible(false);
    playersLives--;
    if (playersLives > 0) {
        respawnShip();
    } else {
        GameTime::schedule(3000, [&]() {
            gameOverCallback();
        });
    }
}

void PlayerManager::respawnShip() {
    GameTime::schedule(1500, [&]() {
        player->position().X(playerSpawnLocation.X());
        player->position().Y(playerSpawnLocation.Y());
        player->position().Rotation(playerSpawnLocation.Rotation());
        player->direction().Angle(playerSpawnLocation.Rotation());
        player->direction().Speed(0);
        player->setVisible(true);
        player->mover().reset();
    });
}

void
PlayerManager::checkCollisionsWithPlayers(EntityList &entityList, std::function<void(Entity *, Entity *)> hitHandler) {
    if (player->isVisible()) {
        entityList.checkCollisions(*player, [&](Entity *hitEnt) {
            hitHandler(player, hitEnt);
        });
    }
}
