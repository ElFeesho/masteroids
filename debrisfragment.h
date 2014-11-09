#ifndef __DEBRIS_H__
#define __DEBRIS_H__

#include "entity.h"
#include "gfx.h"

class DebrisFragment : public Entity
{
public:
	DebrisFragment(Position position, double size, double rotationSpeed, double xspeed, double yspeed, const RGB &colour, long time_to_live);
	~DebrisFragment();
	bool update();
	void render(GfxWrapper *gfx);
	Position &position() { return pos; }
private:
	Position pos;
	int count;
	double xspeed, yspeed;
	double rotationSpeed;
	double size;
	long ttl;
	RGB colour;
};

#endif
