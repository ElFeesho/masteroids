#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include "entity.h"
#include "gfx.h"

#include "fixeddirectionmover.h"

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
private:
	Mover *mover;
	Position pos;
	Shape asteroidShape;
	Direction travelDirection;
	double peaks[6];
	bool alive;
	double rot_speed;
};

#endif
