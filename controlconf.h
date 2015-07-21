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
	ControlConfRenderer() : menu_sel(0)
	{
	}

	~ControlConfRenderer()
	{
	}

    void render(GfxWrapper &gfx, Position &position, Shape &shape, Direction &direction, RGB &colour = RGB::white)
	{
        gfx.drawRect(120, 70, 403, 316, RGB::blue);
        gfx.drawText(false, 135, 80 + gfx.textHeight() * 8, "Not implemented", RGB::white);
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

	bool update()
	{
		return true;
	}

    void render(GfxWrapper &gfx);

	bool buttonDown(GamepadButton button);

	bool buttonUp(GamepadButton button);

	Position &position()
	{
		return Position::NONE;
	}

	Shape &shape()
	{
		return Shape::NONE;
	}

	Direction &direction()
	{
		return Direction::NONE;
	}

	AliveMonitor &aliveMonitor()
	{
		return AlwaysAlive::alivemonitor;
	}

	Renderer &renderer()
	{
		return controlConfRenderer;
	}

    void menuScreenPresented() override;
    void menuScreenHidden() override;

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
