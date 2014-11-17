#include "ship.h"

Ship::Ship(Gamepad *gamepad, ShipListener *listener, ShipMover &shipMover, Position spawnLocation) : visible(true),
                                                                                                     shipRenderer(ShipRenderer()),
                                                                                                     mover(shipMover),
                                                                                                     bodyShape(Shape(8.0f)),
                                                                                                     gamepad(gamepad),
                                                                                                     listener(listener),
                                                                                                     rotationSpeed(0),
                                                                                                     travelDirection(Direction(0.0, 0.0)),
                                                                                                     spawnPosition(spawnLocation) {
    gamepad->addListener(this);
    position().X(spawnLocation.X());
    position().Y(spawnLocation.Y());
    direction().Angle(spawnLocation.Rotation());
    position().Rotation(spawnLocation.Rotation());
}

Ship::~Ship() {
    gamepad->removeListener(this);
}

bool Ship::update() {
    travelDirection.rotate(GameTime::factorTime(rotationSpeed));
    mover.move(direction(), position());
    return aliveMonitor().alive();
}

void Ship::respawn() {
    GameTime::schedule(1500, [&]() {
        position().X(spawnPosition.X());
        position().Y(spawnPosition.Y());
        position().Rotation(spawnPosition.Rotation());
        direction().Angle(spawnPosition.Rotation());
        direction().Speed(0);
        setVisible(true);
        mover.reset();
    });
}

bool Ship::buttonDown(GamepadButton button) {
    if (button == BUTTON_RIGHT) {
        rotationSpeed = 0.075f;
    }
    else if (button == BUTTON_LEFT) {
        rotationSpeed = -0.075f;
    }
    else if (button == BUTTON_UP) {
        travelDirection.Speed(0.1f);
    }
    else if (button == BUTTON_FIRE) {
        listener->shipFired(this);
    }
    return false;
}

bool Ship::buttonUp(GamepadButton button) {
    if (button == BUTTON_LEFT || button == BUTTON_RIGHT) {
        rotationSpeed = 0;
    }
    else if (button == BUTTON_UP) {
        travelDirection.Speed(0.0f);
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
        renderer().render(gfx, position(), shape(), direction());
    }
}


