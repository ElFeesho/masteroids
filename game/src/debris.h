#pragma once

#include "entity.h"

#include "movers/fixeddirectionmover.h"
#include "elapsedtimetolive.h"
#include "renderers/debrisrender.h"

class Debris : public Entity
{
public:
	Debris(Direction travelDirection, Position pos, Shape shape, RGB &debrisColour);

	Position &position();

	Shape &shape();

	Direction &direction();

	AliveMonitor & aliveMonitor();

    void render(Gfx &gfx);

	bool update();

	Renderer & renderer();

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
