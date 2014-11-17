#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "gfx/gfx.h"
#include "position.h"
#include "shape.h"
#include "direction.h"
#include "alivemonitor.h"
#include "entity.h"

class Actor : public Entity
{
public:
    Actor(Renderer *renderer, Mover *mover, AliveMonitor &aliveMonitor);
    virtual ~Actor();

    bool update() override;

    void render(GfxWrapper *gfx) override;

    Position &position() override;

    Shape &shape() override;

    Direction &direction() override;

    AliveMonitor &aliveMonitor() override;

    Renderer &renderer() override;
private:
    Position actorPosition;
    Direction actorDirection;
    Shape actorShape;
    Renderer *actorRenderer;
    AliveMonitor *actorMonitor;
    Mover *actorMover;

};

#endif
