#ifndef __BULLET_H__
#define __BULLET_H__

#include <ogc/lwp_watchdog.h>

#include "entity.h"
#include "gfx.h"
#include "direction.h"
#include "mover.h"
#include "time.h"
#include "elapsedtimetolive.h"

class BulletRenderer : public Renderer
{
public:
	BulletRenderer() {}
	~BulletRenderer() {}
	
	void render(GfxWrapper* gfx, Position& position, Shape& shape, Direction& direction)
	{
		gfx->drawRect(position.X()-shape.Radius(),
					  position.Y()-shape.Radius(),
					  shape.Radius()*2,
					  shape.Radius()*2,
					  RGB::white);
	}
	
};

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
	Renderer& renderer() { return bulletRenderer; }

private:
	ElapsedTimeToLive timeToLive;
	BulletRenderer bulletRenderer;
	BulletMover mover;
	Position pos;
	Direction travelDirection;
	Shape bulletShape;
	Entity *bulletOwner;
};

#endif
