#ifndef DEBRIS_H
#define DEBRIS_H
#include "entity.h"
#include "gfx.h"
#include <cmath>
#include "time.h"

#include "fixeddirectionmover.h"
#include "elapsedtimetolive.h"

class DebrisRenderer : public Renderer
{
public:
	void render(GfxWrapper* gfx, Position& position, Shape& shape, Direction& direction)
	{
		gfx->drawLine(position.X()-cos(position.Rotation())*shape.Radius(),
						position.Y()-sin(position.Rotation())*shape.Radius(),
						position.X()+cos(position.Rotation())*shape.Radius(),
						position.Y()+sin(position.Rotation())*shape.Radius(),
						RGB::white);
	}
};

class Debris : public Entity
{
public:
	Debris(Direction travelDirection, Position pos, Shape shape);
	~Debris();

	Position& position();

	Shape& shape();

	Direction& direction();

	AliveMonitor &aliveMonitor() { return monitor; }

	void render(GfxWrapper* gfx);

	bool update();
	
	Renderer& renderer() { return debrisRenderer; }


private:
	Direction travelDirection;
	Position pos;
	Shape debrisShape;
	DebrisRenderer debrisRenderer;
	ElapsedTimeToLive monitor;
	double rotationSpeed;
	FixedDirectionMover mover;
};

#endif // DEBRIS_H
