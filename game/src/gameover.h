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

	bool update() override;

    void render(Gfx &gfx) override;

	Position &position() override;

	Shape &shape() override;

	Direction &direction() override;

	const AliveMonitor & aliveMonitor() override;

	const Renderer & renderer() override;

	GameOverRenderer gameOverRenderer;
private:
    AlwaysAlive alwaysAliveMonitor;
};

#endif
