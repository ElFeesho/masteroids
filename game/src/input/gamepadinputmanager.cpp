#include "gamepadinputmanager.h"

#include "keyboardsource.h"

static GamepadInputManager instance;

GamepadInputManager::GamepadInputManager() : gamepad{std::unique_ptr<KeyboardSource>(new KeyboardSource())}
{
}

void GamepadInputManager::poll()
{
    gamepad->poll();
}

GamepadSource &GamepadInputManager::inputForPlayer(int)
{
    return *(gamepad.get());
}

GamepadInputManager &GamepadInputManager::sharedInstance()
{
    return instance;
}
