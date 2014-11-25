#include "bullet.h"

Bullet::Bullet(Entity *owner, Direction travelDirection, RGB &bulletColour)
        : mover(BulletMover()),
          bulletRenderer(BulletRenderer()),
          pos(Position(owner->position())),
          travelDirection(travelDirection),
          timeToLive(ElapsedTimeToLive(3000)),
          colour(bulletColour) {
    this->travelDirection.Speed(5.5f);

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
    renderer().render(gfx, position(), shape(), direction(), colour);
}

