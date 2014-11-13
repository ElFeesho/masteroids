#ifndef __SHIP_H__
#define __SHIP_H__

#include "gamepad.h"
#include "entity.h"
#include "gfx.h"

#include "renderers/shiprenderer.h"
#include "movers/shipmover.h"
#include "vector.h"

#include "time.h"



class Ship;

class ShipListener
{
public:
	virtual ~ShipListener(){};
	virtual void shipRequestedPause(Ship *ship) = 0;
	virtual void shipDied(Ship *ship) = 0;
	virtual void shipFired(Ship *ship) = 0;
};

class Ship : public Entity, public GamepadListener
{
public:
	Ship(Gamepad *gamepad, ShipListener *listener);
	~Ship();
	bool update();
	void render(GfxWrapper *gfx);
	
	Gamepad *getGamepad();

   void buttonDown(GamepadButton button);
	void buttonUp(GamepadButton button);

	Position &position() { return pos; }
	Shape &shape() { return bodyShape; }
	Direction &direction() { return travelDirection; }
	AliveMonitor &aliveMonitor() { return AlwaysAlive::alivemonitor; };
	Renderer &renderer() { return shipRenderer; }

private:
	Gamepad *gamepad;
	ShipListener *listener;
	ShipMover mover;
	ShipRenderer shipRenderer;

	Position pos;
	Shape bodyShape;
	double rotationSpeed;
	unsigned long kill_time;
	RGB colour;
	Direction travelDirection;
};

#endif
