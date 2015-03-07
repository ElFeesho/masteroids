#ifndef __INGAME_H__
#define __INGAME_H__

#include "entity.h"
#include "gfx/gfx.h"
#include "input/gamepad.h"
#include "renderers/pausedialogrenderer.h"

class PauseDialogListener
{
public:
	virtual ~PauseDialogListener()
	{
	}

	virtual void ingameContinueSelected() = 0;

	virtual void ingameQuitSelected() = 0;
};

class PauseDialog : public Entity, public GamepadListener
{
public:
	PauseDialog(Gamepad *gamepad, PauseDialogListener *listener);

	~PauseDialog();

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
		return pauseDialogRenderer;
	}

private:
	Gamepad *gamepad;
	PauseDialogListener *listener;
	PauseDialogRenderer pauseDialogRenderer;
	int menu_sel;
};

#endif
