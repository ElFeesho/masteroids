#ifndef __BULLET_GENERATOR_H__
#define __BULLET_GENERATOR_H__

#include "input/gamepad.h"
#include <functional>

class BulletGenerator
{
public:
    BulletGenerator(std::function<void()> fireBullet);

    ~BulletGenerator();

    void attachToButton(GamepadButton &button);

    void detachFromButton(GamepadButton &button);

private:
	std::function<void()> onShouldFireBullet;
};

#endif
