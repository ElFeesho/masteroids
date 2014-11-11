#ifndef DEBRIS_H
#define DEBRIS_H
#include "entity.h"
#include "gfx.h"
#include <cmath>

#include "fixeddirectionmover.h"

class Debris : public Entity
{
public:
	Debris(Direction &direction, Position &position, Shape &shape) : direction(direction), position(position), shape(shape) {
	}
	~Debris() {}

	Position& position() {
		return position;
	}

	Shape& shape() { return shape; }
	
	void render(GfxWrapper* gfx)
	{
		gfx->drawLine(position().X()-cos(position().Rotation())*shape().Radius(), 
						  position().Y()-sin(position().Rotation())*shape().Radius(), 
						  position().X()+cos(position().Rotation())*shape().Radius(), 
						  position().Y()+sin(position().Rotation())*shape().Radius(), 
						  RGB::white);
	}
	
	bool update()
	{
		
		return true;
	}
	
private:
	Direction direction;
	Position position;
	Shape shape;
	FixedDirectionMover mover;
};

#endif // DEBRIS_H
