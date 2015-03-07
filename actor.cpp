#include "actor.h"

Actor::Actor(RGB &colour, Mover *pmover, Renderer *prenderer, AliveMonitor *pmonitor)
		: actorColour(colour),
		  actorDirection(Direction::NONE),
		  actorPosition(Position::NONE),
		  actorShape(Shape::NONE),
		  actorMover(pmover),
		  actorRenderer(prenderer),
		  actorMonitor(pmonitor),
		  visible(true)
{

}

Actor::~Actor()
{

}

bool Actor::update()
{
	mover()->move(direction(), position(), shape());
	return actorMonitor->alive();
}

void Actor::render(GfxWrapper *gfx)
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

AliveMonitor &Actor::aliveMonitor()
{
	return *actorMonitor;
}

Renderer &Actor::renderer()
{
	return *actorRenderer;
}

RGB &Actor::colour()
{
	return actorColour;
}

Mover *Actor::mover()
{
	return actorMover;
}

void Actor::setVisible(bool visible)
{
	this->visible = visible;
}

bool Actor::isVisible()
{
	return visible;
}
