#include "gamepadinputmanager.h"

#include "keyboardsource.h"

GamepadInputManager::GamepadInputManager() : gamepads{new Gamepad(new KeyboardSource()), new Gamepad(new KeyboardSource()), new Gamepad(new KeyboardSource()), new Gamepad(new KeyboardSource())} {}

GamepadInputManager::~GamepadInputManager() {
}

void GamepadInputManager::poll() {
    for(int i = 0; i < 4; i++)
    {
        gamepads[i]->poll();
    }
}

Gamepad* GamepadInputManager::inputForPlayer(int playerNumber) {
    return gamepads[playerNumber];
}

GamepadInputManager *GamepadInputManager::sharedInstance() {
    return instance;
}

GamepadInputManager *GamepadInputManager::instance = new GamepadInputManager(); 