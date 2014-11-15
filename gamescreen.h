#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "screen.h"
#include "entitylist.h"
#include "ship.h"
#include "ingame.h"
#include "debrisfountain.h"

class GameScreen : public Screen, public ShipListener, public InGameListener
{
public:
  GameScreen();
  ~GameScreen();
  void screenHidden();
  void screenShown();
  void update(GfxWrapper* gfx);
  void setListener(ScreenListener* listener);
  
	void shipDied(Ship* ship);
	void shipFired(Ship* ship);
	void shipRequestedPause(Ship* ship);
	
	void ingameContinueSelected();
	void ingameQuitSelected();
	
	void generateLevel();
private:
  ScreenListener* listener;
  EntityList asteroids;
  EntityList secondaryAsteroids;
  
  EntityList debrisEntities;
  DebrisFountain debrisFountain;
  InGame *pauseEnt;
  
  bool isPaused;
  
  Ship *players[4];
  ShipMover playerMovers[4];
  EntityList playerBullets[4];
  int playerScores[4];
  
  int level;
  void checkAsteroidCollisions(int playerNumber);
};

#endif // GAMESCREEN_H
