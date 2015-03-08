#ifndef __BULLET_GENERATOR_H__
#define __BULLET_GENERATOR_H__

#include "input/gamepad.h"
#include <functional>

class BulletGenerator
{
public:
	BulletGenerator(std::function<void()> fireBullet) : onShouldFireBullet(fireBullet)
	{
	};

	~BulletGenerator()
	{
	};

	void attachToButton(GamepadButton &button)
	{
		button.addDownHandler(&onShouldFireBullet);
	}

	void detachFromButton(GamepadButton &button)
	{
		button.removeDownHandler(&onShouldFireBullet);
	}

private:
	std::function<void()> onShouldFireBullet;
};

#endif