#include "debris.h"
#include <cstdlib>

Debris::Debris(Direction ntravelDirection, Position pos, Shape shape, RGB &debrisColour) :
		travelDirection(ntravelDirection),
		pos(pos),
        debrisShape(shape),
        colour(debrisColour),
        rotationSpeed(((rand() % 10) / 10.f) - 0.5f),
        monitor(1500)
{
}

Debris::~Debris()
{

}

Position &Debris::position()
{
	return pos;
}

Shape &Debris::shape()
{
	return debrisShape;
}

Direction &Debris::direction()
{
	return travelDirection;
}

void Debris::render(GfxWrapper &gfx)
{
	renderer().render(gfx, position(), shape(), direction(), colour);
}

bool Debris::update()
{
	mover.move(direction(), position(), shape());
	position().rotate(rotationSpeed);
	return aliveMonitor().alive();
}
