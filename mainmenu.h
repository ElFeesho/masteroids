#ifndef MAINMENU_H
#define MAINMENU_H

#include "entity.h"

class MainMenu : public Entity
{
	MainMenu() {};
	~MainMenu() {};virtual 
	
	bool update();
	void render(GfxWrapper *gfx);
	
	Position& position() { return Position::NONE; }
	Shape& shape() { return Shape::NONE; }
};

#endif // MAINMENU_H
