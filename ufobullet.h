#ifndef __UFOBULLET_H__
#define __UFOBULLET_H__

#include "entity.h"

class UFOBullet : public Entity
{
public:
	UFOBullet();
	UFOBullet(double x, double y, double rot, Entity *ufo);
	~UFOBullet();
	bool update();
private:
	double angle;
	Entity *owner;
	unsigned long ttl;
};

#endif
