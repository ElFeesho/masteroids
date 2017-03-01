#pragma once

#include <memory>
#include <gfx/gfx.h>
#include <actor.h>

#include "movers/shipmover.h"
#include "renderers/shiprenderer.h"

class ShipFactory
{
public:
    Actor* createShip(RGB &colour, Position &spawnLocation)
	{
        Actor* ship = new Actor(colour, shipMover, shipRenderer, std::unique_ptr<AlwaysAlive>(new AlwaysAlive()));
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

