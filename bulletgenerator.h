#ifndef __BULLET_GENERATOR_H__
#define __BULLET_GENERATOR_H__

#include "input/gamepad.h"
#include <functional>

class BulletGenerator : public GamepadListener
{
public:
	BulletGenerator(std::function<void()> fireBullet) : onShouldFireBullet(fireBullet)
	{
	};

	~BulletGenerator()
	{
	};

	virtual bool buttonDown(GamepadButton button) override;

	virtual bool buttonUp(GamepadButton button) override;

private:
	std::function<void()> onShouldFireBullet;
};

#endif