#include <movers/mover.h>
#include "actor.h"

Actor::Actor(Renderer *renderer, Mover *mover, AliveMonitor &aliveMonitor) : actorRenderer(renderer), actorMover(mover), actorMonitor(&aliveMonitor) {
}

Actor::~Actor(){
    delete actorRenderer;
    delete actorMover;
}

bool Actor::update() {
    actorMover->move(direction(), position(), shape());
    return aliveMonitor().alive();
}

void Actor::render(GfxWrapper *gfx) {
    renderer().render(gfx, position(), shape(), direction());
}

Position &Actor::position() {
    return actorPosition;
}

Shape &Actor::shape() {
    return actorShape;
}

Direction &Actor::direction() {
    return actorDirection;
}

AliveMonitor &Actor::aliveMonitor() {
    return *actorMonitor;
}

Renderer &Actor::renderer() {
    return *actorRenderer;
}

