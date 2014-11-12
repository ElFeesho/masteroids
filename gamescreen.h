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
private:
  ScreenListener* listener;
  EntityList asteroids;
  EntityList secondaryAsteroids;
  EntityList playerBullets[4];
  
  EntityList debrisEntities;
  DebrisFountain debrisFountain;
  InGame *pauseEnt;
  
  bool isPaused;
  
  Ship *playerOne;
  Ship *playerTwo;
  Ship *playerThree;
  Ship *playerFour;
};

#endif // GAMESCREEN_H
