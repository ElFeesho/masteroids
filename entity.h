#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "position.h"

class GfxWrapper;

class Engine;

class Entity
{
public:
	virtual ~Entity() {};

	virtual bool update() = 0;
	virtual void render(GfxWrapper *gfx) = 0;
	
	virtual Position &position() = 0;
};

#endif
