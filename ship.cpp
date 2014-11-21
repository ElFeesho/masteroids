#include "ship.h"

Ship::Ship(Gamepad *gamepad, ShipListener *listener, ShipMover &shipMover) : visible(true),
                                                                                                     shipRenderer(ShipRenderer()),
                                                                                                     shipMover(shipMover),
                                                                                                     bodyShape(Shape(8.0f)),
                                                                                                     gamepad(gamepad),
                                                                                                     listener(listener),
                                                                                                     travelDirection(Direction(0.0, 0.0)),
                                                                                                     colour(RGB::white) {
    gamepad->addListener(this);
}

Ship::~Ship() {
    gamepad->removeListener(this);
}

bool Ship::update() {
    mover().move(direction(), position());
    return aliveMonitor().alive();
}

bool Ship::buttonDown(GamepadButton button) {
    if (button == BUTTON_RIGHT) {
        direction().Spin(0.075f);
    }
    else if (button == BUTTON_LEFT) {
        direction().Spin(-0.075f);
    }
    else if (button == BUTTON_UP) {
        direction().Speed(0.1f);
    }
    else if (button == BUTTON_FIRE) {
        listener->shipFired(this);
    }
    return false;
}

bool Ship::buttonUp(GamepadButton button) {
    if (button == BUTTON_LEFT || button == BUTTON_RIGHT) {
        direction().Spin(0.0f);
    }
    else if (button == BUTTON_UP) {
        direction().Speed(0.0f);
    }
    else if (button == BUTTON_START) {
        listener->shipRequestedPause(this);
    }
    return false;
}

Gamepad *Ship::getGamepad() {
    return gamepad;
}

void Ship::render(GfxWrapper *gfx) {
    if (isVisible()) {
        renderer().render(gfx, position(), shape(), direction(), colour);
    }
}