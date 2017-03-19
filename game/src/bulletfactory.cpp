#include "bulletfactory.h"

Actor *BulletFactory::createBullet(RGB &colour, Direction direction, Position position) {
    Actor *bullet = new Actor(colour, mover, renderer, std::unique_ptr<ElapsedTimeToLive>(new ElapsedTimeToLive(3000)));
    bullet->direction().set(direction);
    bullet->position().set(position.X(), position.Y(), position.Rotation());
    bullet->shape().Radius(1.0f);
    return bullet;
}
