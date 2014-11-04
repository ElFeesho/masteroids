#ifndef __MENU_H__
#define __MENU_H__

#include "entity.h"
#include "gfx.h"

class Menu : public Entity
{
public:
	Menu();
	~Menu();
	bool update(GfxWrapper *gfx);
private:
	unsigned int menu_sel;
	unsigned long next_change;
	char ldir;
	bool active;
	Entity *child;
	RGB borderColour;
	RGB textColour;
	RGB highlightColour;
};

#endif
