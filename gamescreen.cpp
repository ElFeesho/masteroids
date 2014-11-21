#include "gamescreen.h"
#include "asteroid.h"
#include "bullet.h"
#include "input/gamepadinputmanager.h"
#include "options.h"

using std::stringstream;

GameScreen::GameScreen() :
        isPaused(false),
        level(0),
        playerScores{0, 0, 0, 0},
        pauseEnt(NULL),
        playerMovers{ShipMover(), ShipMover(), ShipMover(), ShipMover()},
        playerScorePositions{Position(5, 5, 0), Position(635, 5, 0), Position(5, 440, 0), Position(635, 440, 0)},
        playerColours{RGB::green, RGB::yellow, RGB::blue, RGB::purple},
        livesRenderer(LivesRenderer()) {

}

GameScreen::~GameScreen() {

}

void GameScreen::screenHidden() {
    asteroids.clear();
    secondaryAsteroids.clear();
    debrisEntities.clear();
    if (pauseEnt != NULL) {
        isPaused = false;
        delete pauseEnt;
        pauseEnt = NULL;
    }

    for (int i = 0; i < Options::players; i++) {
        delete players[i];
        playersLives[i] = 0;
        playerMovers[i].reset();
        playerBullets[i].clear();
        playerScores[i] = 0;
    }
}

void GameScreen::screenShown() {
    if (Options::players == 1) {
        playerSpawnLocations[0] = Position(320, 240, -M_PI_2);
    }
    else if (Options::players == 2) {
        playerSpawnLocations[0] = Position(160, 240, 0);
        playerSpawnLocations[1] = Position(480, 240, -M_PI);
    }
    else if (Options::players == 3) {
        playerSpawnLocations[0] = Position(320, 120, M_PI_2);
        playerSpawnLocations[1] = Position(160, 320, -M_PI_4);
        playerSpawnLocations[2] = Position(480, 320, -M_PI_4*3);
    }
    else if (Options::players == 4) {
        playerSpawnLocations[0] = Position(160, 120, M_PI_4);
        playerSpawnLocations[1] = Position(480, 120, M_PI_4*3);
        playerSpawnLocations[2] = Position(160, 320, -M_PI_4);
        playerSpawnLocations[3] = Position(480, 320, -M_PI_4*3);
    }

    for (int i = 0; i < Options::players; i++) {
        playersLives[i] = Options::lives;
        players[i] = new Ship(GamepadInputManager::sharedInstance()->inputForPlayer(i), this, playerMovers[i]);
        players[i]->position().X(playerSpawnLocations[i].X());
        players[i]->position().Y(playerSpawnLocations[i].Y());
        players[i]->position().Rotation(playerSpawnLocations[i].Rotation());
        players[i]->direction().Angle(playerSpawnLocations[i].Rotation());
        players[i]->direction().Speed(0);
        players[i]->setColour(playerColours[i]);
        players[i]->setVisible(true);
    }

    generateLevel();
}

void GameScreen::generateLevel() {
    for (int i = 0; i < 7 + (level / 2); i++) {
        asteroids.add(new Asteroid());
    }
}

void GameScreen::update(GfxWrapper *gfx) {
    if (!isPaused) {
        debrisEntities.updateAll();
        debrisEntities.renderAll(gfx);

        updatePlayers(gfx);

        asteroids.updateAll();
        asteroids.renderAll(gfx);

        secondaryAsteroids.updateAll();
        secondaryAsteroids.renderAll(gfx);

        checkPlayerDeaths();
    }
    else {
        asteroids.renderAll(gfx);
        pauseEnt->update();
        pauseEnt->render(gfx);
    }

}

void GameScreen::checkPlayerDeaths() {
    for (int i = 0; i < Options::players; i++) {
        if (!players[i]->isVisible()) {
            continue;
        }

        if (Options::team_kill) {
            for (int j = 0; j < Options::players; j++) {

                if (i == j) {
                    continue;
                }

                playerBullets[j].checkCollisions(*players[i], [&](Entity *hit) {
                    killPlayer(i);
                    playerBullets[j].removeEntity(hit);
                });
            }
        }

        asteroids.checkCollisions(*players[i], [&](Entity *hit) {
            killPlayer(i);
            asteroids.removeEntity(hit);
            secondaryAsteroids.add(new Asteroid(10.0f, Position(hit->position())));
            secondaryAsteroids.add(new Asteroid(10.0f, Position(hit->position())));
        });

        secondaryAsteroids.checkCollisions(*players[i], [&](Entity *hit) {
            killPlayer(i);
            secondaryAsteroids.removeEntity(hit);

            checkLevelComplete();
        });

    }
}

void GameScreen::killPlayer(int playerNumber) {
    debrisFountain.projectDebris(debrisEntities, Direction(0.5f, players[playerNumber]->direction().Angle()), players[playerNumber]->position(), 1.3f, 12, playerColours[playerNumber]);
    players[playerNumber]->setVisible(false);
    playersLives[playerNumber]--;
    if (playersLives[playerNumber] > 0) {

        respawnShip(playerNumber);
        playerMovers[playerNumber].reset();
    }
    else {
        bool shouldGoToGameover = true;
        for (int i = 0; i < Options::players; i++) {
            shouldGoToGameover &= playersLives[i] == 0;
        }

        if (shouldGoToGameover) {
            GameTime::schedule(3000, [&]() {
                listener->screenClosed(this, 0);
            });
        }
    }
}

void GameScreen::updatePlayers(GfxWrapper *gfx) {
    for (int i = 0; i < Options::players; i++) {
        players[i]->update();
        players[i]->render(gfx);
        playerBullets[i].updateAll();
        playerBullets[i].renderAll(gfx);

        checkAsteroidCollisions(i);

        scoreRenderer.setScore(playerScores[i]);
        livesRenderer.setLives(playersLives[i]);
        TextAlignment alignment = i & 1 ? RIGHT : LEFT;
        scoreRenderer.setAlignment(alignment);
        livesRenderer.setAlignment(alignment);

        scoreRenderer.render(gfx, playerScorePositions[i], Shape::NONE, Direction::NONE, playerColours[i]);
        livesRenderer.render(gfx, playerScorePositions[i], Shape::NONE, Direction::NONE, playerColours[i]);
    }
}


void GameScreen::checkAsteroidCollisions(int playerNumber) {
    asteroids.checkCollisions(playerBullets[playerNumber], [&](Entity *asteroid, Entity *bullet) {
        debrisFountain.projectDebris(debrisEntities, asteroid->direction(), asteroid->position(), 1.3f, 6, RGB::white);
        secondaryAsteroids.add(new Asteroid(10.0f, Position(asteroid->position())));
        secondaryAsteroids.add(new Asteroid(10.0f, Position(asteroid->position())));
        playerBullets[playerNumber].removeEntity(bullet);
        playerScores[playerNumber] += 10;
        asteroids.removeEntity(asteroid);
    });

    secondaryAsteroids.checkCollisions(playerBullets[playerNumber], [&](Entity *asteroid, Entity *bullet) {
        debrisFountain.projectDebris(debrisEntities, asteroid->direction(), asteroid->position(), 1.3f, 6, RGB::white);
        playerBullets[playerNumber].removeEntity(bullet);
        playerScores[playerNumber] += 25;
        secondaryAsteroids.removeEntity(asteroid);

        checkLevelComplete();
    });
}


void GameScreen::setListener(ScreenListener *listener) {
    this->listener = listener;
}

void GameScreen::shipFired(Ship *ship) {
    for (int i = 0; i < Options::players; i++) {
        if (ship == players[i] && playerBullets[i].size() < Options::max_bullets && players[i]->isVisible()) {
            playerBullets[i].add(new Bullet(ship, ship->direction(), playerColours[i]));
            break;
        }
    }
}

void GameScreen::shipRequestedPause(Ship *ship) {
    isPaused = true;
    pauseEnt = new InGame(ship->getGamepad(), this);
}

void GameScreen::ingameContinueSelected() {
    isPaused = false;
    delete pauseEnt;
    pauseEnt = NULL;
}

void GameScreen::ingameQuitSelected() {
    listener->screenClosed(this, 0);
}

void GameScreen::respawnShip(int playerNumber) {
    GameTime::schedule(1500, [&, playerNumber]() {
        players[playerNumber]->position().X(playerSpawnLocations[playerNumber].X());
        players[playerNumber]->position().Y(playerSpawnLocations[playerNumber].Y());
        players[playerNumber]->position().Rotation(playerSpawnLocations[playerNumber].Rotation());
        players[playerNumber]->direction().Angle(playerSpawnLocations[playerNumber].Rotation());
        players[playerNumber]->direction().Speed(0);
        players[playerNumber]->setVisible(true);
        players[playerNumber]->mover().reset();
    });
}

void GameScreen::checkLevelComplete() {
    if (asteroids.size() == 0 && secondaryAsteroids.size() == 0) {
        GameTime::schedule(1500, [&]() {
            level++;
            generateLevel();
        });
    }
}
