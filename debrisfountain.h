#ifndef DEBRISFOUNTAIN_H
#define DEBRISFOUNTAIN_H

#include "entitylist.h"
#include "direction.h"
#include "position.h"

#include "debris.h"

class DebrisFountain {
public:
    DebrisFountain();

    ~DebrisFountain();

    void projectDebris(EntityList &entityList, Direction direction, Position from, double spread, int amount, RGB &colour);
};

#endif // DEBRISFOUNTAIN_H
