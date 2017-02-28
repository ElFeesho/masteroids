#pragma once

#include <memory>

#include "movers/mover.h"
#include "entity.h"

class Actor : public Entity
{
public:
    Actor(RGB &colour, Mover &mover, const Renderer &prenderer, std::unique_ptr<AliveMonitor> aliveMonitor);

	Position &position() override;

	Direction &direction() override;

	Shape &shape() override;

    RGB &colour();

    const AliveMonitor &aliveMonitor() override;

    Mover &mover();

    const Renderer &renderer() override;

    bool update() override;

    void render(Gfx &gfx) override;

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
