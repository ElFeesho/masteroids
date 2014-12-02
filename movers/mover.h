#ifndef __MOVER_H__
#define __MOVER_H__

#include "../position.h"
#include "../direction.h"
#include "../shape.h"

class Mover {
public:
    virtual ~Mover() {
    };

    virtual void move(Direction &direction, Position &position, Shape &shape = Shape::NONE) = 0;
    virtual void reset() = 0;
};

#endif
