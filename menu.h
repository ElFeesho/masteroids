#ifndef __MENU_H__
#define __MENU_H__

#include "entity.h"

class Menu : public Entity
{
public:
	Menu();
	~Menu();
	bool update();
private:
	unsigned int menu_sel;
	unsigned long next_change;
	char ldir;
	bool active;
	Entity *child;
};

#endif
