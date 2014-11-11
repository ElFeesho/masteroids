#ifndef __BULLET_H__
#define __BULLET_H__

#include <ogc/lwp_watchdog.h>

#include "entity.h"
#include "gfx.h"
#include "direction.h"
#include "mover.h"

class BulletMover : public Mover
{
public:
	BulletMover() : direction(Direction::NONE) {}
	~BulletMover() {}

	void move(Position &position) {
		position.translate(cos(direction.Angle())*direction.Speed(), sin(direction.Angle())*direction.Speed());
	};

	void setDirection(Direction &direction)
	{
		this->direction = Direction(direction.Speed(), direction.Angle());
		this->direction.Speed(this->direction.Speed()+5.0f);
	}
private:
	Direction direction;
};

class Bullet : public Entity
{
public:
	Bullet(Entity *owner, Direction &travelDirection);

	~Bullet() {};
	bool update();
	void render(GfxWrapper *gfx);
	Position& position() { return pos; }
	Shape &shape() { return bulletShape; }

private:
	BulletMover mover;
	Position pos;
	Direction direction;
	Shape bulletShape;
	Entity *bulletOwner;
	unsigned long ttl;
};

#endif
