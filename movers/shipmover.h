#ifndef __SHIPMOVER_H__
#define __SHIPMOVER_H__

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

#endif