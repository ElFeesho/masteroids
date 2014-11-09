#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "position.h"

class GfxWrapper;

class Engine;

class Entity
{
public:
	Entity(){};
	virtual ~Entity() {};

	virtual bool update() = 0;
	virtual void render(GfxWrapper *gfx) = 0;
	
	Position &position();
private:
	Position pos;
};

#endif
