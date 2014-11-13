#ifndef __OPTIONS_H__
#define __OPTIONS_H__

#include "entity.h"
#include "input/gamepad.h"
#include "gfx/gfx.h"

#include <string.h>

#include "renderers/optionsrenderer.h"

class OptionsListener
{
public:
	virtual ~OptionsListener() {};
	virtual void optionsControllerConfigSelected() = 0;
	virtual void optionsMenuClosed() = 0;
};

class Options : public Entity, public GamepadListener
{
public:
	Options(OptionsListener *listener);
	~Options();
	bool update();
	void render(GfxWrapper *gfx);

	Position& position() { return Position::NONE; }
	Shape& shape() { return Shape::NONE; }
	Direction& direction() { return Direction::NONE; }
	AliveMonitor &aliveMonitor() { return AlwaysAlive::alivemonitor; }
	Renderer& renderer() { return optionsRenderer; }

	void buttonDown(GamepadButton button);
	void buttonUp(GamepadButton button);

	static int lives;
	static int difficulty;
	static bool team_kill;
	static int players;
	static int max_bullets;
	static bool music;
private:
	OptionsListener *listener;
	OptionsRenderer optionsRenderer;
	bool alive;
	int menu_sel;
	unsigned long next_change;
	char ldir;
	RGB colour;
	RGB colourHighlight;
	Entity *child;
};

#endif
