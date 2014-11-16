#include "gamescreen.h"
#include "asteroid.h"
#include "bullet.h"
#include "input/gamepadinputmanager.h"
#include "options.h"
#include <sstream>

using std::stringstream;

GameScreen::GameScreen() :
        isPaused(false),
        level(0),
        playerScores({0,0,0,0}),
        playerMovers({ShipMover(), ShipMover(), ShipMover(), ShipMover()}),
        playerScorePositions({ Vector(5,5), Vector(635, 5), Vector(5, 460), Vector(635, 460) })
{
}

GameScreen::~GameScreen()
{

}

void GameScreen::screenHidden()
{
	asteroids.clear();
    secondaryAsteroids.clear();
    debrisEntities.clear();
	if(pauseEnt != NULL)
	{
		isPaused = false;
		delete pauseEnt;
		pauseEnt = NULL;
	}

    for(int i = 0; i < Options::players; i++)
    {
        delete players[i];
        playersLives[i] = 0;
        playerMovers[i].reset();
        playerBullets[i].clear();
        playerScores[i] = 0;
    }
}

void GameScreen::screenShown()
{
	if(Options::players == 1)
	{
		playerSpawnLocations[0] = Position(320,240,0); 
	}
	else if(Options::players == 2)
	{
		playerSpawnLocations[0] = Position(160, 240, 0);
		playerSpawnLocations[1] = Position(480, 240, 0);
	}
	else if(Options::players == 3)
	{
		playerSpawnLocations[0] = Position(320, 120, 0);
		playerSpawnLocations[1] = Position(160, 320, 0);
		playerSpawnLocations[2] = Position(480, 320, 0);
	}
	else if(Options::players == 4)
	{
		playerSpawnLocations[0] = Position(160, 120, 0);
		playerSpawnLocations[1] = Position(480, 120, 0);
		playerSpawnLocations[2] = Position(160, 320, 0);
		playerSpawnLocations[3] = Position(480, 320, 0);
	}
	
	for(int i = 0; i < Options::players; i++)
	{
        playersLives[i] = Options::lives;
		players[i] = new Ship(GamepadInputManager::sharedInstance()->playerOne(), this, playerMovers[i], playerSpawnLocations[i]);
	}
	
	generateLevel();
}

void GameScreen::generateLevel()
{
	for(int i = 0; i < 7 + (level/2); i++)
	{
		asteroids.add(new Asteroid());
	}
}

void GameScreen::update(GfxWrapper* gfx)
{
	if(!isPaused)
	{
		debrisEntities.updateAll();
		debrisEntities.renderAll(gfx);

		updatePlayers(gfx);

		asteroids.updateAll();
		asteroids.renderAll(gfx);

		secondaryAsteroids.updateAll();
		secondaryAsteroids.renderAll(gfx);

        checkPlayerDeaths();

        if(asteroids.size() == 0 && secondaryAsteroids.size() == 0)
		{
			level++;
			generateLevel();
		}
	}
	else
	{
		asteroids.renderAll(gfx);
		pauseEnt->update();
		pauseEnt->render(gfx);
	}
	
}

void GameScreen::checkPlayerDeaths() {
    for(int i = 0; i < Options::players; i++) {
        asteroids.checkCollisions(*players[i], [&](Entity *hit) {
            if (players[i]->isVisible()) {
                debrisFountain.projectDebris(debrisEntities, Direction(3.5, players[i]->direction().Angle()), players[i]->position(), 1.3f, 12);
                players[i]->setVisible(false);
                playersLives[i]--;
                if(playersLives[i]>0) {
                    players[i]->respawn();
                    playerMovers[i].reset();
                }
                else
                {
                    bool shouldGoToGameover = true;
                    for(int j = 0; j < Options::players; j++)
                    {
                        shouldGoToGameover &= playersLives[j] == 0;
                    }

                    if(shouldGoToGameover)
                    {
                        GameTime::schedule(3000, [&](){
                           listener->screenClosed(this, 0);
                        });
                    }
                }
            }
        });
    }
}

void GameScreen::updatePlayers(GfxWrapper *gfx)
{
	for(int i = 0; i<Options::players; i++)
	{
		players[i]->update();
		players[i]->render(gfx);
		playerBullets[i].updateAll();
		playerBullets[i].renderAll(gfx);
			
		checkAsteroidCollisions(i);
		stringstream sstream;
		sstream << "SCORE: " << playerScores[i];
		gfx->drawText(playerScorePositions[i].X(), playerScorePositions[i].Y(), sstream.str(), RGB::green, i & 1 ? RIGHT : LEFT);
	}
}


void GameScreen::checkAsteroidCollisions(int playerNumber)
{
	asteroids.checkCollisions(playerBullets[playerNumber], [&](Entity* asteroid, Entity* bullet) {
		debrisFountain.projectDebris(debrisEntities, asteroid->direction(), asteroid->position(), 1.3f, 6);
		secondaryAsteroids.add(new Asteroid(10.0f, Position(asteroid->position())));
		secondaryAsteroids.add(new Asteroid(10.0f, Position(asteroid->position())));
		playerBullets[playerNumber].removeEntity(bullet);
		playerScores[playerNumber] += 10;
		asteroids.removeEntity(asteroid);
	});

	secondaryAsteroids.checkCollisions(playerBullets[playerNumber], [&](Entity* asteroid, Entity* bullet) {
		debrisFountain.projectDebris(debrisEntities, asteroid->direction(), asteroid->position(), 1.3f, 6);
		playerBullets[playerNumber].removeEntity(bullet);
		playerScores[playerNumber] += 25;
		secondaryAsteroids.removeEntity(asteroid);
	});
}


void GameScreen::setListener(ScreenListener* listener)
{
  this->listener = listener;
}

void GameScreen::shipDied(Ship* ship)
{

}

void GameScreen::shipFired(Ship* ship)
{
	for(int i = 0; i < Options::players; i++)
	{
		if(ship == players[i])
		{
			playerBullets[i].add(new Bullet(ship, ship->direction()));
			break;
			
		}
	}
}

void GameScreen::shipRequestedPause(Ship* ship)
{
	isPaused = true;
	pauseEnt = new InGame(ship->getGamepad(), this);
}

void GameScreen::ingameContinueSelected()
{
	isPaused = false;
	delete pauseEnt;
	pauseEnt = NULL;
}

void GameScreen::ingameQuitSelected()
{
	listener->screenClosed(this, 0);
}
