#ifndef __CONTROL_CONF_H__
#define __CONTROL_CONF_H__

#include "entity.h"
#include "gfx.h"
#include "gamepad.h"

/*
	Input is not that difficult...
*/

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

private:
	ControlConfListener *listener;
	bool alive;
	int menu_sel;
	int binding;
	unsigned long bind_timeout;
	unsigned long next_change;
	char ldir;
};

#endif
