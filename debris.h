#ifndef DEBRIS_H
#define DEBRIS_H
#include "entity.h"
#include "gfx.h"
#include <cmath>

#include "fixeddirectionmover.h"

class Debris : public Entity
{
public:
	Debris(Direction direction, Position pos, Shape shape);
	~Debris();

	Position& position();

	Shape& shape();
	
	void render(GfxWrapper* gfx);
	
	bool update();
	
private:
	Direction direction;
	Position pos;
	Shape debrisShape;
	FixedDirectionMover mover;
};

#endif // DEBRIS_H
