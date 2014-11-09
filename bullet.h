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
	bool update();
	void render(GfxWrapper *gfx);
	Position& position();
	Shape &shape() { return bulletShape; }
private:
	Position pos;
	Shape bulletShape;
	RGB col;
	Entity *owner;
	unsigned long ttl;
};

#endif
