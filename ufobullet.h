#ifndef __UFOBULLET_H__
#define __UFOBULLET_H__

#include "entity.h"

#include "gfx.h"

class UFOBullet : public Entity
{
public:
	UFOBullet();
	UFOBullet(double x, double y, double rot, Entity *ufo);
	~UFOBullet();
	bool update();
	void render(GfxWrapper *gfx);
	Position &position() { return pos; }
private:
	Position pos;
	double angle;
	Entity *owner;
	unsigned long ttl;
};

#endif
