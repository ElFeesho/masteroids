#ifndef __MENU_H__
#define __MENU_H__

#include "entity.h"
#include "gfx/gfx.h"
#include "input/gamepad.h"
#include "images/asteroid_banner.h"
#include "images/controllers.h"
#include "renderers/menurenderer.h"
#include "menuscreenitem.h"

class MenuListener
{
public:
	virtual ~MenuListener()
	{
	};

	virtual void menuStartGameSelected() = 0;

	virtual void menuOptionsSelected() = 0;

	virtual void menuAboutSelected() = 0;
};

class Menu : public MenuScreenItem
{
public:
	Menu(MenuListener *listener);

	~Menu();

    void menuScreenPresented() override;
    void menuScreenHidden() override;

	bool update();

    void render(GfxWrapper &gfx);

	void incrementMenu();

	void decrementMenu();

	void handleMenuSelection();

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
        return alwaysAliveMonitor;
	}

	Renderer &renderer()
	{
		return menuRenderer;
	}

private:
    AlwaysAlive alwaysAliveMonitor;
	MenuListener *listener;
	MenuRenderer menuRenderer;
	unsigned int menu_sel;
	unsigned long next_change;
	char ldir;
	Position pos;
};

#endif
