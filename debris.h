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

	Position &position() override;
	Shape &shape() override;
	Direction &direction() override;

    void render(Gfx &gfx) override;
	bool update() override;

	const AliveMonitor & aliveMonitor() override;
	const Renderer & renderer() override;

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
