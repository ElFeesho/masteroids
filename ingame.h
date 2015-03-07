#ifndef __INGAME_H__
#define __INGAME_H__

#include "entity.h"
#include "gfx/gfx.h"
#include "input/gamepad.h"
#include "renderers/ingamemenurenderer.h"

class InGameListener
{
public:
	virtual ~InGameListener()
	{
	}

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

	bool buttonDown(GamepadButton button);

	bool buttonUp(GamepadButton button);

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
		return AlwaysAlive::alivemonitor;
	}

	Renderer &renderer()
	{
		return ingameRenderer;
	}

private:
	Gamepad *gamepad;
	InGameListener *listener;
	InGameMenuRenderer ingameRenderer;
	int menu_sel;
};

#endif
