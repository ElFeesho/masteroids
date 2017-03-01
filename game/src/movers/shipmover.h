#pragma once

#include <movers/mover.h>
#include <vector.h>
#include "gametime.h"

#include <iostream>

class ShipMover : public Mover
{
public:
    void move(Direction &direction, Position &position, Shape &shape = Shape::NONE);

    void reset();

private:
	Vector movementVector{ 0, 0 };
};

