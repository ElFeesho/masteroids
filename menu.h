#ifndef __MENU_H__
#define __MENU_H__

#include "entity.h"
#include "gfx.h"
#include "gamepad.h"

class Menu : public Entity, public GamepadListener
{
public:
	Menu();
	~Menu();
	bool update(GfxWrapper *gfx);

	void incrementMenu();
	void decrementMenu();
	void handleMenuSelection();

	void buttonDown(GamepadButton button);
	void buttonUp(GamepadButton button);
private:
	unsigned int menu_sel;
	unsigned long next_change;
	char ldir;
	bool active;
	Entity *child;
};

#endif
