#ifndef __MENU_H__
#define __MENU_H__

#include "entity.h"
#include "gfx.h"
#include "gamepad.h"
#include "asteroid_banner.h"
#include "font5.h"
#include "controllers.h"
#include "renderers/menurenderer.h"

class MenuListener
{
public:
	virtual ~MenuListener(){};
	virtual void menuStartGameSelected() = 0;
	virtual void menuOptionsSelected() = 0;
	virtual void menuAboutSelected() = 0;
};

class Menu : public Entity, public GamepadListener
{
public:
	Menu(MenuListener *listener);
	~Menu();
	bool update();
	void render(GfxWrapper *gfx);

	void incrementMenu();
	void decrementMenu();
	void handleMenuSelection();

	void buttonDown(GamepadButton button);
	void buttonUp(GamepadButton button);

	Position &position() { return Position::NONE; }
	Shape &shape() { return Shape::NONE; }
	Direction& direction() { return Direction::NONE; }
	AliveMonitor &aliveMonitor() { return AlwaysAlive::alivemonitor; }
	Renderer &renderer() { return menuRenderer; }
private:
	MenuListener *listener;
	MenuRenderer menuRenderer;
	unsigned int menu_sel;
	unsigned long next_change;
	char ldir;
	bool active;
	Entity *child;
	Position pos;
};

#endif
