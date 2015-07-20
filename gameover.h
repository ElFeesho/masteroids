#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "entity.h"
#include "gfx/gfx.h"
#include "input/gamepad.h"
#include "renderers/gameoverrenderer.h"

class GameOver : public Entity
{
public:
	GameOver();

	~GameOver();

	bool update();

    void render(GfxWrapper &gfx);

	Position &position() override;

	Shape &shape() override;

	Direction &direction() override;

	AliveMonitor &aliveMonitor() override;

	Renderer &renderer() override;

	GameOverRenderer gameOverRenderer;
};

#endif
