#ifndef __SHIP_H__
#define __SHIP_H__

#include "gamepad.h"
#include "entity.h"
#include "gfx.h"

#include "mover.h"
#include "vector.h"

#include "time.h"

class ShipMover : public Mover
{
public:
	ShipMover() : movementVector(Vector(0, 0)) {}

	~ShipMover() {}

	void move(Direction &direction, Position &position, Shape &shape = Shape::NONE)
	{
		movementVector.add(Time::factorTime(cos(direction.Angle())*direction.Speed()), Time::factorTime(sin(direction.Angle())*direction.Speed()));
		position.translate(movementVector.X(), movementVector.Y());

		if(position.X()>640.0+10.0)
		{
			position.X(-10.0);
		}
		else if(position.X()<0.0-10.0)
		{
			position.X(640.0+10.0);
		}

		if(position.Y()>480.0+10.0)
		{
			position.Y(-10.0);
		}
		else if(position.Y()<0.0-10.0)
		{
			position.Y(480.0+10.0);
		}
	}

private:
	Vector movementVector;
};

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
	void on_hit();

	Gamepad *getGamepad();

   void buttonDown(GamepadButton button);
	void buttonUp(GamepadButton button);

	Position &position() { return pos; }
	Shape &shape() { return bodyShape; }
	Direction &direction() { return travelDirection; }
	AliveMonitor &aliveMonitor() { return AlwaysAlive::alivemonitor; };

private:
	Gamepad *gamepad;
	ShipListener *listener;
	ShipMover mover;

	Position pos;
	Shape bodyShape;
	double rotationSpeed;
	unsigned long kill_time;
	RGB colour;
	Direction travelDirection;
};

#endif
