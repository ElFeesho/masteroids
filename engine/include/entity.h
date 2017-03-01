#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <position.h>
#include <shape.h>
#include <direction.h>
#include "alivemonitor.h"
#include <renderer.h>

class Gfx;

class Entity
{
public:
	virtual ~Entity() {}

	virtual bool update() = 0;

    virtual void render(Gfx &gfx) = 0;

	virtual Position &position() = 0;

	virtual Shape &shape() = 0;

	virtual Direction &direction() = 0;

    virtual const AliveMonitor &aliveMonitor() = 0;

    virtual const Renderer &renderer() = 0;
};

#endif
