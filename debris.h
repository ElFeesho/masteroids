#pragma once

#include "entity.h"

#include "movers/fixeddirectionmover.h"
#include "elapsedtimetolive.h"
#include "renderers/debrisrender.h"

class Debris : public Entity
{
public:
	Debris(Direction travelDirection, Position pos, Shape shape, RGB &debrisColour);

	~Debris();

	Position &position();

	Shape &shape();

	Direction &direction();

	AliveMonitor &aliveMonitor()
	{
		return monitor;
	}

    void render(GfxWrapper &gfx);

	bool update();

	Renderer &renderer()
	{
		return debrisRenderer;
	}


private:
	Direction travelDirection;
	Position pos;
	Shape debrisShape;
    RGB colour;
	DebrisRenderer debrisRenderer;
    double rotationSpeed;
    ElapsedTimeToLive monitor;
	FixedDirectionMover mover;

};
