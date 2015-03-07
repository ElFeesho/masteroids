#include "bulletgenerator.h"

bool BulletGenerator::buttonDown(GamepadButton button){
	if(button == BUTTON_FIRE)
		onShouldFireBullet();
	return false;
}

bool BulletGenerator::buttonUp(GamepadButton button)
{
	return false;
}
