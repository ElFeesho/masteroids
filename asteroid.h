#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include <cmath>

#include "entity.h"

#include "movers/fixeddirectionmover.h"
#include "renderers/asteroidrenderer.h"

class Asteroid : public Entity
{
public:
	Asteroid();
	Asteroid(double scale, const Position& nposition);
	~Asteroid();

	bool update();
	void render(GfxWrapper *gfx);
	Position &position() { return pos; }
	Shape &shape() { return asteroidShape; }
	Direction& direction() { return travelDirection; }
	AliveMonitor &aliveMonitor() { return AlwaysAlive::alivemonitor; }
	Renderer& renderer() { return astroRenderer; }
private:
	Mover *mover;
	Position pos;
	Shape asteroidShape;
	AsteroidRenderer astroRenderer;
	Direction travelDirection;
	double peaks[6];
	double rot_speed;
};

#endif
