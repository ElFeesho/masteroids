#ifndef __MENU_H__
#define __MENU_H__

#include "entity.h"
#include "gfx.h"
#include "gamepad.h"

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
private:
	MenuListener *listener;
	unsigned int menu_sel;
	unsigned long next_change;
	char ldir;
	bool active;
	Entity *child;
	Position pos;
};

#endif
