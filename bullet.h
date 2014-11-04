#ifndef __BULLET_H__
#define __BULLET_H__

#include "entity.h"
#include "gfx.h"

class Bullet : public Entity
{
public:
	Bullet();
	Bullet(double x, double y, double rot, const RGB &color, Entity *player);
	~Bullet();
	bool update(GfxWrapper *gfx);
private:
	double angle;
	RGB col;
	Entity *owner;
	unsigned long ttl;
};

#endif
