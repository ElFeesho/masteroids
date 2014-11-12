#ifndef DEBRIS_H
#define DEBRIS_H
#include "entity.h"
#include "gfx.h"
#include <cmath>

#include "fixeddirectionmover.h"

class Debris : public Entity
{
public:
	Debris(Direction travelDirection, Position pos, Shape shape);
	~Debris();

	Position& position();

	Shape& shape();
	
	Direction& direction();
	
	void render(GfxWrapper* gfx);
	
	bool update();
	
private:
	long ttl;
	Direction travelDirection;
	Position pos;
	Shape debrisShape;
	double rotationSpeed;
	FixedDirectionMover mover;
};

#endif // DEBRIS_H
