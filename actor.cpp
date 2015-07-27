#include <iostream>
#include "actor.h"

Actor::Actor(RGB &colour, Mover &pmover, const Renderer &prenderer, std::unique_ptr<AliveMonitor> pmonitor)
		: actorColour(colour),
          actorMover(pmover),
          actorDirection(Direction::NONE),
          actorPosition(Position::NONE),
          actorShape(Shape::NONE),
          actorMonitor(std::move(pmonitor)),
          actorRenderer(prenderer),
		  visible(true)
{
	std::cout << "Actor" << std::endl;
}

Actor::~Actor()
{
	std::cout << "~Actor" << std::endl;
}

bool Actor::update()
{
    mover().move(direction(), position(), shape());
    return actorMonitor->alive();
}

void Actor::render(Gfx &gfx)
{
	if (isVisible())
	{
		renderer().render(gfx, position(), shape(), direction(), colour());
	}
}

Position &Actor::position()
{
	return actorPosition;
}

Shape &Actor::shape()
{
	return actorShape;
}

Direction &Actor::direction()
{
	return actorDirection;
}

const AliveMonitor &Actor::aliveMonitor()
{
    return *(actorMonitor.get());
}

const Renderer &Actor::renderer()
{
    return actorRenderer;
}

RGB &Actor::colour()
{
	return actorColour;
}

Mover &Actor::mover()
{
	return actorMover;
}

void Actor::setVisible(bool nvisible)
{
	this->visible = nvisible;
}

bool Actor::isVisible()
{
	return visible;
}
