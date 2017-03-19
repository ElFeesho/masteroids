#include "shipfactory.h"

#include <actor.h>

Actor *ShipFactory::createShip(RGB &colour, Position &spawnLocation) {
    Actor *ship = new Actor(colour, shipMover, shipRenderer, std::unique_ptr<AlwaysAlive>(new AlwaysAlive()));
    ship->position().X(spawnLocation.X());
    ship->position().Y(spawnLocation.Y());
    ship->position().Rotation(spawnLocation.Rotation());
    ship->shape().Radius(10);
    return ship;
}
