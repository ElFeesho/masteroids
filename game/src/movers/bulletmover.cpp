#include <cmath>
#include <iostream>
#include "bulletmover.h"

BulletMover::BulletMover() {
}

BulletMover::~BulletMover() {
}

void BulletMover::move(Direction &direction, Position &position, Shape &) {
    position.translate(GameTime::factorTime(cos(direction.Angle() * direction.Speed())),
                       GameTime::factorTime(sin(direction.Angle() * direction.Speed())));

    if (position.X() > 640) {
        position.X(0);
    }
    else if (position.X() < 0) {
        position.X(640);
    }

    if (position.Y() > 480) {
        position.Y(0);
    }
    else if (position.Y() < 0) {
        position.Y(480);
    }
}

void BulletMover::reset() {

}