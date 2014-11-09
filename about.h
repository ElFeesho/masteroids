#ifndef __ABOUT_H__
#define __ABOUT_H__

#include "entity.h"
#include "gfx.h"
#include "gamepad.h"

class AboutListener
{
public:
	virtual ~AboutListener() {}
	virtual void aboutClosed() = 0;
};

class About : public Entity, public GamepadListener
{
public:
	About(AboutListener *listener);
	~About();
	bool update() { return true; }
	void render(GfxWrapper *gfx);
	
	void buttonUp(GamepadButton button);
	void buttonDown(GamepadButton button);
	
	Position& position() { return Position::NONE; }
	Shape& shape() { return Shape::NONE; }

private:
	AboutListener *listener;
};

#endif
