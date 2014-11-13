#ifndef __BULLET_H__
#define __BULLET_H__

#include <ogc/lwp_watchdog.h>

#include "entity.h"
#include "gfx.h"
#include "direction.h"
#include "mover.h"
#include "time.h"
#include "elapsedtimetolive.h"

class BulletMover : public Mover
{
public:
	BulletMover() {}
	~BulletMover() {}

	void move(Direction &direction, Position &position, Shape &shape = Shape::NONE) {
		position.translate(Time::factorTime(cos(direction.Angle())*direction.Speed()), Time::factorTime(sin(direction.Angle())*direction.Speed()));
	}
};

class Bullet : public Entity
{
public:
	Bullet(Entity *owner, Direction travelDirection);

	~Bullet() {};
	bool update();
	void render(GfxWrapper *gfx);
	Position& position() { return pos; }
	Shape &shape() { return bulletShape; }
	Direction& direction() { return travelDirection; }
	AliveMonitor &aliveMonitor() { return timeToLive; }

private:
	ElapsedTimeToLive timeToLive;
	BulletMover mover;
	Position pos;
	Direction travelDirection;
	Shape bulletShape;
	Entity *bulletOwner;
};

#endif
