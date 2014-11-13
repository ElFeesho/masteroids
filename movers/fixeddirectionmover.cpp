#include "fixeddirectionmover.h"
#include "time.h"

void FixedDirectionMover::move(Direction &direction, Position& position, Shape &shape)
{
	position.translate(Time::factorTime(cos(direction.Angle())*direction.Speed()), Time::factorTime(sin(direction.Angle())*direction.Speed()));

	double radius = shape.Radius();
	if(position.X()>640.0f+radius)
	{
		position.X(0.0f-radius);
	}

	if(position.X()<0.0f-radius)
	{
		position.X(640.0f+radius);
	}

	if(position.Y()>480.0f+radius)
	{
		position.Y(0.0f-radius);
	}

	if(position.Y()<0.0f-radius)
	{
		position.Y(480.0f+radius);
	}
}
