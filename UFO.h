#ifndef __UFO_H__
#define __UFO_H__

#include "entity.h"
#include "gfx/gfx.h"

class UFO : public Entity
{
public:
	UFO();
	~UFO();
	bool update(GfxWrapper *gfx);
	void on_hit();
	Position &position() { return pos; }
	Shape &shape() { return ufoShape; }
private:
	Shape ufoShape;
	double xspeed;
	double yspeed;
	unsigned long next_think;
	unsigned long next_fire;
	bool alive;
	RGB shipColour;
	Position pos;
};

#endif
