#ifndef __INGAME_H__
#define __INGAME_H__

#include "entity.h"
#include "gfx.h"
#include "gamepad.h"

class InGameMenuRenderer : public Renderer 
{
public:
	InGameMenuRenderer() : menu_sel(0) {}
	~InGameMenuRenderer() {}
	
	void render(GfxWrapper* gfx, Position& position, Shape& shape, Direction& direction)
	{
		gfx->drawRect((320-150), 240-50, 300, 90, RGB::blue);

		gfx->drawText(320-80, 240-40, "Quit Current Game?", RGB::white);
		if(menu_sel==0)
		{
			gfx->drawText(320-140, 240-5, "Continue", RGB::yellow);
		}
		else
		{
			gfx->drawText(320-140, 240-5, "Continue", RGB::white);
		}
		
		if(menu_sel==1)
		{
			gfx->drawText(420, 240-5, "Exit", RGB::yellow);
		}
		else
		{
			gfx->drawText(420, 240-5, "Exit", RGB::white);
		}
	}
private:
	int menu_sel;
};

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
	AliveMonitor &aliveMonitor() { return AlwaysAlive::alivemonitor; }
	Renderer &renderer(){ return ingameRenderer; }
private:
	Gamepad *gamepad;
	InGameListener *listener;
	InGameMenuRenderer ingameRenderer;
	int menu_sel;
};

#endif
