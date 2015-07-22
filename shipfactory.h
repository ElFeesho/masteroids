#ifndef __SHIPFACTORY_H__
#define __SHIPFACTORY_H__

#include "movers/shipmover.h"
#include "renderers/shiprenderer.h"
#include "gfx/gfx.h"
#include "actor.h"

class ShipFactory
{
public:
    ShipFactory() : shipMover(ShipMover()), shipRenderer(ShipRenderer())
	{
	}

	~ShipFactory()
	{
	}

	Actor *createShip(RGB &colour, Position &spawnLocation)
	{
        Actor *ship = new Actor(colour, shipMover, shipRenderer, AlwaysAlive::alivemonitor);
		ship->position().X(spawnLocation.X());
		ship->position().Y(spawnLocation.Y());
		ship->position().Rotation(spawnLocation.Rotation());
		ship->shape().Radius(10);
		return ship;
	}

private:
    ShipMover shipMover;
    ShipRenderer shipRenderer;
};

#endif
