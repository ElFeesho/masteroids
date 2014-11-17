#ifndef FIXEDDIRECTIONMOVER_H
#define FIXEDDIRECTIONMOVER_H

#include "mover.h"
#include <cmath>

class FixedDirectionMover : public Mover {
public:
    FixedDirectionMover() {
    }

    ~FixedDirectionMover() {
    }

    void move(Direction &direction, Position &position, Shape &shape);
};

#endif // FIXEDDIRECTIONMOVER_H