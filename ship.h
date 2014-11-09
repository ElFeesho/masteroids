#ifndef __SHIP_H__
#define __SHIP_H__

#include "gamepad.h"

#include "collobj.h"
#include "gfx.h"

class Ship;

class ShipListener
{
public:
	virtual ~ShipListener(){};
	virtual void shipRequestedPause(Ship *ship) = 0;
	virtual void shipDied(Ship *ship) = 0;
	virtual void shipFired(Ship *ship) = 0;
};

class Ship : public Collobj, public GamepadListener
{
public:
	Ship(Gamepad *gamepad, ShipListener *listener);
	Ship(int padnum);
	~Ship();
	void inc_bfired();
	void dec_bfired();
	bool update();
	void render(GfxWrapper *gfx);
	void add_score(int am);
	void on_hit();
	void draw_lives(GfxWrapper *gfx);
	int get_lives();
	int get_score();
	
	Gamepad *getGamepad();
	
   void buttonDown(GamepadButton button);
	void buttonUp(GamepadButton button);
	
	static Ship *players[4];
	static int scores[4];
private:
  Gamepad *gamepad;
  ShipListener *listener;
	int player_num;
	double rot; /* Ship Rot */
	double angle;	/* Travel Angle */
	double xspeed, yspeed, rotationSpeed;
	int bullets_fired;
	int score;
	int llevel;
	int lives;
	unsigned long kill_time;
	RGB colour;
	double propulsion;
};

#endif
