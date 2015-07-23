#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "movers/mover.h"
#include "entity.h"

class Actor : public Entity
{
public:
    Actor(RGB &colour, Mover &mover, const Renderer &prenderer, std::unique_ptr<AliveMonitor> aliveMonitor);

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
	RGB actorColour;
    Mover &actorMover;
	Direction actorDirection;
	Position actorPosition;
	Shape actorShape;
    std::unique_ptr<AliveMonitor> actorMonitor;
    const Renderer &actorRenderer;
	bool visible{true};
};

#endif
