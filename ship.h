#ifndef __SHIP_H__
#define __SHIP_H__

#include "input/gamepad.h"
#include "entity.h"
#include "gfx/gfx.h"

#include "renderers/shiprenderer.h"
#include "movers/shipmover.h"
#include "vector.h"

#include "time.h"

class Ship;

class ShipListener {
public:
    virtual ~ShipListener() {
    };

    virtual void shipRequestedPause(Ship *ship) = 0;

    virtual void shipFired(Ship *ship) = 0;
};

class Ship : public Entity, public GamepadListener {
public:
    Ship(Gamepad *gamepad, ShipListener *listener, ShipMover &shipMover, Position spawnLocation);

    ~Ship();

    bool update();

    void render(GfxWrapper *gfx);

    Gamepad *getGamepad();

    bool buttonDown(GamepadButton button);

    bool buttonUp(GamepadButton button);

    Position &position() {
        return pos;
    }

    Shape &shape() {
        return bodyShape;
    }

    Direction &direction() {
        return travelDirection;
    }

    AliveMonitor &aliveMonitor() {
        return AlwaysAlive::alivemonitor;
    };

    Renderer &renderer() {
        return shipRenderer;
    }

    bool isVisible() {
        return visible;
    }

    void setVisible(bool visibility) {
        visible = visibility;
    }

    void respawn();

private:
    Gamepad *gamepad;
    ShipListener *listener;
    ShipMover mover;
    ShipRenderer shipRenderer;

    Position spawnPosition;

    Position pos;
    Shape bodyShape;
    double rotationSpeed;
    Direction travelDirection;

    bool visible;
};

#endif
