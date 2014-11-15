#include "fixeddirectionmover.h"
#include "gametime.h"

void FixedDirectionMover::move(Direction &direction, Position& position, Shape &shape)
{
	position.translate(GameTime::factorTime(cos(direction.Angle())*direction.Speed()), GameTime::factorTime(sin(direction.Angle())*direction.Speed()));

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
