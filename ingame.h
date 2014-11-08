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
	bool update(GfxWrapper *gfx);
	void buttonDown(GamepadButton button);
	void buttonUp(GamepadButton button);
private:
	Gamepad *gamepad;
	InGameListener *listener;
	int menu_sel;
	RGB colour;
	RGB colourHighlight;
};

#endif
