#include "fixeddirectionmover.h"

void FixedDirectionMover::move(Direction &direction, Position& position)
{
	position.translate(cos(direction.Angle())*direction.Speed(), sin(direction.Angle())*direction.Speed());
}