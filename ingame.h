#ifndef __INGAME_H__
#define __INGAME_H__

#include "entity.h"
#include "gfx.h"
#include "gamepad.h"

class InGameListener
{
public:
	virtual ~InGameListener(){}
	virtual void ingameContinueSelected() = 0;
	virtual void ingameQuitSelected() = 0;
};

class InGame : public Entity, public GamepadListener
{
public:
	InGame(Gamepad *gamepad, InGameListener *listener);
	~InGame();
	bool update();
	void render(GfxWrapper *gfx);
	void buttonDown(GamepadButton button);
	void buttonUp(GamepadButton button);
	Position &position() { return Position::NONE; }
	Shape &shape() { return Shape::NONE; }
	Direction &direction() { return Direction::NONE; }
private:
	Gamepad *gamepad;
	InGameListener *listener;
	int menu_sel;
};

#endif
