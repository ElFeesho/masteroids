#ifndef __ABOUT_H__
#define __ABOUT_H__

#include "entity.h"
#include "gfx.h"
#include "gamepad.h"

class About : public GamepadListener
{
public:
	About();
	~About();
	bool update();
	void render(GfxWrapper *gfx);
	
	void buttonUp(GamepadButton button);
	void buttonDown(GamepadButton button);
private:
	bool alive;
};

#endif
