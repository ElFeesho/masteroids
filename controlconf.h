#ifndef __CONTROL_CONF_H__
#define __CONTROL_CONF_H__

#include "entity.h"
#include "gfx.h"
#include "gamepad.h"
#include "font5.h"
#include "options.h"
#include "controls_img.h"
/*
	Input is not that difficult...
*/

class ControlConfRenderer : public Renderer
{
public:
	ControlConfRenderer() : menu_sel(0) {}
	~ControlConfRenderer() {}
	
	void render(GfxWrapper* gfx, Position& position, Shape& shape, Direction& direction)
	{
		gfx->drawRect(120, 70, 403, 316, RGB::blue);
		gfx->drawText(135, 80+font5_char_high*8, "Not implemented", RGB::white);
	}
	
	void setMenuSelection(int menuSelection)
	{
		menu_sel = menuSelection;
	}
private:
	int menu_sel;
};

class ControlConfListener
{
public:
	virtual ~ControlConfListener() {};
	virtual void controlConfClosed() = 0;
};

class ControlConf : public Entity, public GamepadListener
{
public:
	ControlConf(ControlConfListener *listener);
	~ControlConf();
	bool update() { return true; }
	void render(GfxWrapper *gfx);

	void buttonDown(GamepadButton button);
	void buttonUp(GamepadButton button);

	Position &position() { return Position::NONE; }
	Shape &shape() { return Shape::NONE; }
	Direction &direction() { return Direction::NONE; }
	AliveMonitor &aliveMonitor() { return AlwaysAlive::alivemonitor; }
	Renderer &renderer() { return controlConfRenderer; }

private:
	ControlConfListener *listener;
	ControlConfRenderer controlConfRenderer;
	bool alive;
	int menu_sel;
	int binding;
	unsigned long bind_timeout;
	unsigned long next_change;
	char ldir;
};

#endif
