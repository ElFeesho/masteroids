#include "bulletgenerator.h"

BulletGenerator::BulletGenerator(std::function<void ()> fireBullet) : onShouldFireBullet(fireBullet)
{
}

BulletGenerator::~BulletGenerator()
{
}

void BulletGenerator::attachToButton(GamepadButton &button)
{
    button.addDownHandler(&onShouldFireBullet);
}

void BulletGenerator::detachFromButton(GamepadButton &button)
{
    button.removeDownHandler(&onShouldFireBullet);
}
