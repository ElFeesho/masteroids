#pragma once

#include <memory>
#include "gamepad.h"

class GamepadInputManager
{
public:
    GamepadInputManager();

    static GamepadInputManager &sharedInstance();

    void poll();

    GamepadSource &inputForPlayer(int playerNumber);

private:
    std::unique_ptr<GamepadSource> gamepad;
};
