#include "gamepadinputmanager.h"

#include "keyboardsource.h"

GamepadInputManager::GamepadInputManager() {
    // Not sure how this should actually work ...
    gamepadOne = new Gamepad(new KeyboardSource());
}

GamepadInputManager::~GamepadInputManager() {
}

void GamepadInputManager::poll() {
    gamepadOne->poll();
}

Gamepad *GamepadInputManager::playerOne() {
    return gamepadOne;
}

Gamepad *GamepadInputManager::playerTwo() {
    return gamepadTwo;
}

Gamepad *GamepadInputManager::playerThree() {
    return gamepadThree;
}

Gamepad *GamepadInputManager::playerFour() {
    return gamepadFour;
}


GamepadInputManager *GamepadInputManager::sharedInstance() {
    return instance;
}

GamepadInputManager *GamepadInputManager::instance = new GamepadInputManager(); 