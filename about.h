#ifndef __ABOUT_H__
#define __ABOUT_H__

#include "renderers/aboutrenderer.h"
#include "entity.h"
#include "gfx/gfx.h"
#include "input/gamepad.h"

class AboutListener {
public:
    virtual ~AboutListener() {
    }

    virtual void aboutClosed() = 0;
};

class About : public Entity, public GamepadListener {
public:
    About(AboutListener *listener);

    ~About();

    bool update() {
        return aliveMonitor().alive();
    }

    void render(GfxWrapper *gfx);

    bool buttonUp(GamepadButton button);

    bool buttonDown(GamepadButton button);

    Position &position() {
        return Position::NONE;
    }

    Shape &shape() {
        return Shape::NONE;
    }

    Direction &direction() {
        return Direction::NONE;
    }

    AliveMonitor &aliveMonitor() {
        return AlwaysAlive::alwaysAlive;
    }

    Renderer &renderer() {
        return aboutRenderer;
    }

    bool isVisible() { return true; }

    void setVisible(bool visible) { };

private:
    AboutListener *listener;
    AboutRenderer aboutRenderer;
};

#endif
