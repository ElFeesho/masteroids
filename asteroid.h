#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include "entity.h"
#include "gfx.h"

class Asteroid : public Entity
{
public:
	Asteroid();
	Asteroid(double scale);
	~Asteroid();

	bool update();
	void render(GfxWrapper *gfx);
	void on_hit();
	static int count;
	Position &position() { return pos; }
	Shape &shape() { return asteroidShape; }
private:
	Position pos;
	Shape asteroidShape;
	double peaks[6];
	double speed;
	bool alive;
	double rot_speed;
	double trav_ang;
	RGB colour;
};

#endif
