#pragma once

#include <gfx/gfx.h>

#include "movers/shipmover.h"
#include "renderers/shiprenderer.h"

class Actor;

class ShipFactory
{
public:
    Actor* createShip(RGB &colour, Position &spawnLocation);
private:
    ShipMover shipMover;
    ShipRenderer shipRenderer;
};

