#ifndef __ACTOR_H__
#define __ACTOR_H__

#include <movers/mover.h>
#include "entity.h"

class Actor : public Entity
{
public:
	Actor(RGB &colour, Mover *pmover, Renderer *prenderer, AliveMonitor *pmonitor);

	~Actor();

	Position &position();

	Direction &direction();

	Shape &shape();

	RGB &colour();

	AliveMonitor &aliveMonitor();

	Mover *mover();

	Renderer &renderer();

	bool update();

	void render(GfxWrapper *gfx);

	void setVisible(bool visible);

	bool isVisible();

private:
	Mover *actorMover;
	RGB actorColour;
	Direction actorDirection;
	Position actorPosition;
	Shape actorShape;
	AliveMonitor *actorMonitor;
	Renderer *actorRenderer;
	bool visible{true};
};

#endif