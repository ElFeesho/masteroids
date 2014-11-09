#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include "collobj.h"
#include "gfx.h"

class Asteroid : public Collobj
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
private:
	Position pos;
	double peaks[6];
	double speed;
	bool alive;
	double rot_speed;
	double trav_ang;
	RGB colour;
};

#endif
