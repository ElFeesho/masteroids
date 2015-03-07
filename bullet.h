#ifndef __BULLET_H__
#define __BULLET_H__

#include <ogc/lwp_watchdog.h>

#include "entity.h"
#include "gfx/gfx.h"
#include "direction.h"
#include "movers/mover.h"
#include "time.h"
#include "elapsedtimetolive.h"

#include "movers/bulletmover.h"
#include "renderers/bulletrenderer.h"

class Bullet : public Entity
{
public:
	Bullet(Entity *owner, Direction travelDirection, RGB &bulletColour);

	~Bullet()
	{
	};

	bool update();

	void render(GfxWrapper *gfx);

	Position &position()
	{
		return pos;
	}

	Shape &shape()
	{
		return bulletShape;
	}

	Direction &direction()
	{
		return travelDirection;
	}

	AliveMonitor &aliveMonitor()
	{
		return timeToLive;
	}

	Renderer &renderer()
	{
		return bulletRenderer;
	}

private:
	ElapsedTimeToLive timeToLive;
	BulletRenderer bulletRenderer;
	BulletMover mover;
	Position pos;
	Direction travelDirection;
	Shape bulletShape;
	RGB colour;
};

#endif
