#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "entity.h"
#include "gfx/gfx.h"
#include "input/gamepad.h"
#include "renderers/gameoverrenderer.h"

class GameOver : public Entity, public GamepadListener {
public:
    GameOver();

    ~GameOver();

    bool update();

    void render(GfxWrapper *gfx);

    Position &position() override;

    Shape &shape() override;

    Direction &direction() override;

    AliveMonitor &aliveMonitor() override;

    Renderer &renderer() override;

    bool buttonDown(GamepadButton button);

    bool buttonUp(GamepadButton button);

    GameOverRenderer gameOverRenderer;

    bool isVisible() { return true; }

    void setVisible(bool visible) { };
};

#endif
