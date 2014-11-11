#include "fixeddirectionmover.h"

FixedDirectionMover::FixedDirectionMover(Direction direction) : direction(direction)
{
	
}

FixedDirectionMover::~FixedDirectionMover() {}

void FixedDirectionMover::move(Position& position)
{
	position.translate(cos(direction.Angle())*direction.Speed(), sin(direction.Angle())*direction.Speed());
}

void FixedDirectionMover::setDirection(Direction& direction)
{
	this->direction = direction;
}
