#ifndef __CONTROL_CONF_H__
#define __CONTROL_CONF_H__

#include "entity.h"
#include "gfx/gfx.h"
#include "input/gamepad.h"
#include "font5.h"
#include "options.h"
#include "images/controls_img.h"

#include "menuscreenitem.h"

/*
	Input is not that difficult...
*/

class ControlConfRenderer : public Renderer
{
public:
	ControlConfRenderer()
	{
	}

	~ControlConfRenderer()
	{
	}

    void render(Gfx &gfx, Position &, Shape &, Direction &, RGB &) const
	{
        gfx.drawRect(120, 70, 403, 316, RGB::BLUE);
        gfx.drawText(false, 135, 80 + gfx.measureText("W").h * 8, "Not implemented", RGB::WHITE);
	}
};

class ControlConfListener
{
public:
	virtual ~ControlConfListener()
	{
	};

	virtual void controlConfClosed() = 0;
};

class ControlConf : public MenuScreenItem
{
public:
	ControlConf(ControlConfListener *listener);

	~ControlConf();

	bool update();

    void render(Gfx &gfx);

	bool buttonDown(GamepadButton button);

	bool buttonUp(GamepadButton button);

	Position & position();

	Shape & shape();

	Direction & direction();

	AliveMonitor &aliveMonitor();

	Renderer & renderer();

    void menuScreenPresented() override;
    void menuScreenHidden() override;

private:
    AlwaysAlive alwaysAliveMonitor;
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
