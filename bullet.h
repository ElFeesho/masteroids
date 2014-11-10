#ifndef __BULLET_H__
#define __BULLET_H__

#include "entity.h"
#include "gfx.h"
#include "direction.h"
#include "mover.h"


class BulletMover : public Mover
{
public:
	BulletMover(const Direction &direction) : direction(direction) {}
	~BulletMover() {};

	void move(Position &position) {
		position.translate(cos(direction.Angle())*direction.Speed(), sin(direction.Angle())*direction.Speed());
	};

	void setDirection(Direction &direction)
	{
		this->direction = Direction(direction);
		this->direction.Speed(this->direction.Speed()+5.0f);
	}
private:
	Direction direction;
};

class Bullet : public Entity
{
public:
	Bullet(Entity *owner, Direction &directon) : mover(BulletMover(direction)), pos(Position(owner->position())), bulletOwner(owner), direction(Direction(direction)) 
	{
		position().X(owner->position().X());
		position().Y(owner->position().Y());
		position().Rotation(direction.Angle());
		position().translate(0.0f, 0.5f);
		shape().Radius(1.0f);
	}
	
	~Bullet();
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
