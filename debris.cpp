#include "debris.h"

Debris::Debris()
{

}

Debris::~Debris()
{

}
Debris::Debris(Direction direction, Position pos, Shape shape): direction(direction), pos(pos), debrisShape(shape), mover(FixedDirectionMover(direction)) 
{
	
}

Debris::~Debris(){}

Position& Debris::position()
{
	return pos;
}

Shape& Debris::shape()
{ 
	return debrisShape; 
}

void Debris::render(GfxWrapper* gfx)
{
	printf("POS: %.2f %.2f %.2f\n", position().X(), position().Y(), shape().Radius());
	gfx->drawLine(position().X()-cos(position().Rotation())*shape().Radius(), 
						position().Y()-sin(position().Rotation())*shape().Radius(), 
						position().X()+cos(position().Rotation())*shape().Radius(), 
						position().Y()+sin(position().Rotation())*shape().Radius(), 
						RGB::white);
}

bool Debris::update()
{
	mover.move(position());
	return true;
}
