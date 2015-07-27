#include <iostream>
#include "fixeddirectionmover.h"
#include "gametime.h"

FixedDirectionMover::FixedDirectionMover() {
    std::cout << "FixedDirectionMover" << std::endl;
}

FixedDirectionMover::~FixedDirectionMover() {
    std::cout << "~FixedDirectionMover" << std::endl;
}

void FixedDirectionMover::move(Direction &direction, Position &position, Shape &shape) {
    position.rotate(GameTime::factorTime(direction.Spin()));
    position.translate(GameTime::factorTime(cos(direction.Angle()) * direction.Speed()),
                       GameTime::factorTime(sin(direction.Angle()) * direction.Speed()));

    if (position.X() > 640.0f) {
        position.X(0.0f);
    }

    if (position.X() < 0.0f) {
        position.X(640.0f);
    }

    if (position.Y() > 480.0f) {
        position.Y(0.0f);
    }

    if (position.Y() < 0.0f) {
        position.Y(480.0f);
    }
}

void FixedDirectionMover::reset() {

}
