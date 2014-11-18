#ifndef __SHIPMOVER_H__
#define __SHIPMOVER_H__

#include "mover.h"
#include "vector.h"
#include "gametime.h"

class ShipMover : public Mover {
public:
    ShipMover() : movementVector(Vector(0, 0)) {
    }

    ~ShipMover() {
    }

    void move(Direction &direction, Position &position, Shape &shape = Shape::NONE) {
        direction.rotate(GameTime::factorTime(direction.Spin()));
        movementVector.add(GameTime::factorTime(cos(direction.Angle()) * direction.Speed()), GameTime::factorTime(sin(direction.Angle()) * direction.Speed()));
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

    void reset() {
        movementVector.X(0);
        movementVector.Y(0);
    }

private:
    Vector movementVector;
};

#endif