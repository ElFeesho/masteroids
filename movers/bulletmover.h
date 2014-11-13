#ifndef __BULLET_MOVER_H__
#define __BULLET_MOVER_H__

#include "mover.h"
#include "time.h"

class BulletMover : public Mover
{
public:
	BulletMover() {}
	~BulletMover() {}

	void move(Direction &direction, Position &position, Shape &shape = Shape::NONE) {
		position.translate(Time::factorTime(cos(direction.Angle())*direction.Speed()), Time::factorTime(sin(direction.Angle())*direction.Speed()));
	}
};

#endif