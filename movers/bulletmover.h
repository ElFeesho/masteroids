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
		
		if(position.X() > 640)
		{
			position.X(0);
		}
		else if(position.X() < 0)
		{
			position.X(640);
		}
		
		if(position.Y() > 480)
		{
			position.Y(0);
		}
		else if(position.Y() < 0)
		{
			position.Y(480);
		}
	}
};

#endif