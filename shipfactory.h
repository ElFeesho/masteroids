#ifndef __SHIPFACTORY_H__
#define __SHIPFACTORY_H__

#include "actor.h"
#include "renderers/shiprenderer.h"
#include "movers/shipmover.h"

class ShipFactory
{
public:
    static Entity *createShip()
    {
        Entity *ship = new Actor(new ShipRenderer(), new ShipMover(), AlwaysAlive::alwaysAlive);
        ship->shape().Radius(7.5f);
        return ship;
    }
};

#endif