#include "movers/shipmover.h"

ShipMover::ShipMover() : movementVector(0, 0) {
    std::cout << "ShipMover ctor " << this << std::endl;
}

ShipMover::~ShipMover() {
    std::cout << "ShipMover dtor " << this << std::endl;
}

void ShipMover::move(Direction &direction, Position &position, Shape &) {
    direction.rotate(GameTime::factorTime(direction.Spin()));
    movementVector.add(GameTime::factorTime(cos(direction.Angle()) * direction.Speed()),
                       GameTime::factorTime(sin(direction.Angle()) * direction.Speed()));
    position.translate(movementVector.X(), movementVector.Y());

    if (position.X() > 640.0) {
        position.X(0);
    }
    else if (position.X() < 0.0) {
        position.X(640.0);
    }

    if (position.Y() > 480.0) {
        position.Y(0.0);
    }
    else if (position.Y() < 0.0) {
        position.Y(480.0);
    }
}

void ShipMover::reset() {
    movementVector.X(0);
    movementVector.Y(0);
}
