#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "movers/mover.h"
#include "entity.h"

class Actor : public Entity
{
public:
    Actor(RGB &colour, Mover &mover, const Renderer &prenderer, const AliveMonitor &pmonitor);

	~Actor();

	Position &position();

	Direction &direction();

	Shape &shape();

    RGB &colour();

    const AliveMonitor &aliveMonitor() override;

    Mover &mover();

    const Renderer &renderer() override;

    bool update() override;

    void render(GfxWrapper &gfx) override;

    void setVisible(bool visible);

	bool isVisible();

private:
    Mover &actorMover;
	RGB actorColour;
	Direction actorDirection;
	Position actorPosition;
	Shape actorShape;
    const AliveMonitor &actorMonitor;
    const Renderer &actorRenderer;
	bool visible{true};
};

#endif
