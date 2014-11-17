#include "bullet.h"

Bullet::Bullet(Entity *owner, Direction travelDirection)
        : mover(BulletMover()),
          bulletRenderer(BulletRenderer()),
          pos(Position(owner->position())),
          bulletOwner(owner),
          travelDirection(travelDirection),
          timeToLive(ElapsedTimeToLive(3000)) {
    this->travelDirection.Speed(3.5f);

    position().X(owner->position().X());
    position().Y(owner->position().Y());
    position().Rotation(direction().Angle());
    position().translate(0.0f, 0.5f);
    shape().Radius(1.0f);
}

bool Bullet::update() {
    mover.move(direction(), position());
    return aliveMonitor().alive();
}

void Bullet::render(GfxWrapper *gfx) {
    renderer().render(gfx, position(), shape(), direction());
}

