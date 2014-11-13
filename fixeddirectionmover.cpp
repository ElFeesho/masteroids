#include "fixeddirectionmover.h"
#include "time.h"

void FixedDirectionMover::move(Direction &direction, Position& position)
{
	position.translate(Time::factorTime(cos(direction.Angle())*direction.Speed()), Time::factorTime(sin(direction.Angle())*direction.Speed()));
}
