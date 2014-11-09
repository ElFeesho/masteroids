#ifndef __DEBRIS_H__
#define __DEBRIS_H__

#include "entity.h"
#include "gfx.h"

class Debris : public Entity
{
public:
	Debris(int amount, double xpos, double ypos, double angle, double xspeed, double yspeed, const RGB &colour, long time_to_live);
	~Debris();
	bool update();
	void render(GfxWrapper *gfx);
private:
	
	int count;
	double x[16];
	double y[16];
	double angles[16];
	double xsp[16];
	double ysp[16];
	long ttl;
	double rot_speed[16];
	int sizes[16];
	RGB colour;
};

#endif
