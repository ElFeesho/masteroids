#ifndef DEBRIS_H
#define DEBRIS_H

#include "entity.h"

#include "movers/fixeddirectionmover.h"
#include "elapsedtimetolive.h"
#include "renderers/debrisrender.h"

class Debris : public Entity {
public:
    Debris(Direction travelDirection, Position pos, Shape shape);

    ~Debris();

    Position &position();

    Shape &shape();

    Direction &direction();

    AliveMonitor &aliveMonitor() {
        return monitor;
    }

    void render(GfxWrapper *gfx);

    bool update();

    Renderer &renderer() {
        return debrisRenderer;
    }


private:
    Direction travelDirection;
    Position pos;
    Shape debrisShape;
    DebrisRenderer debrisRenderer;
    ElapsedTimeToLive monitor;
    double rotationSpeed;
    FixedDirectionMover mover;
};

#endif // DEBRIS_H
