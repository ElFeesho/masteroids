#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "entity.h"
#include "gfx.h"
#include "gamepad.h"

class GameOver : public Entity, public GamepadListener
{
public:
	GameOver();
	~GameOver();
	bool update();
	void render(GfxWrapper *gfx);

	void buttonDown(GamepadButton button);
	void buttonUp(GamepadButton button);
private:
	RGB colour;
	RGB colourHighlight;
};

#endif
