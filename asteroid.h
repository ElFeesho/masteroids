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
private:
	Mover *mover;
	Position pos;
	Shape asteroidShape;
	double peaks[6];
	bool alive;
	double rot_speed;
};

#endif
