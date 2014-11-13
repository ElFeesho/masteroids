#include "debris.h"
#include <cstdlib>
#include <ogc/lwp_watchdog.h>

Debris::Debris(Direction ntravelDirection, Position pos, Shape shape) : 
	travelDirection(ntravelDirection), 
	pos(pos), 
	debrisShape(shape), 
	mover(FixedDirectionMover()), 
	rotationSpeed(((rand()%10)/10.f)-0.5f),
	ttl(3000)
{
	ttl += ticks_to_millisecs(gettime());
}

Debris::~Debris()
{
	
}

Position& Debris::position()
{
	return pos;
}

Shape& Debris::shape()
{ 
	return debrisShape; 
}

Direction& Debris::direction()
{
	return travelDirection;
}


void Debris::render(GfxWrapper* gfx)
{
	position().rotate(rotationSpeed);
	gfx->drawLine(position().X()-cos(position().Rotation())*shape().Radius(), 
						position().Y()-sin(position().Rotation())*shape().Radius(), 
						position().X()+cos(position().Rotation())*shape().Radius(), 
						position().Y()+sin(position().Rotation())*shape().Radius(), 
						RGB::white);
}

bool Debris::update()
{
	mover.move(direction(), position());
	return ticks_to_millisecs(gettime())<ttl;
}
