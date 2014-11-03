#ifndef __BULLET_H__
#define __BULLET_H__

#include "entity.h"

class Bullet : public Entity
{
public:
	Bullet();
	Bullet(double x, double y, double rot, unsigned short color, Entity *player);
	~Bullet();
	bool update();
private:
	double angle;
	unsigned short col;
	Entity *owner;
	unsigned long ttl;
};

#endif
