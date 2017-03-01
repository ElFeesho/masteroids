#pragma once

#include <memory>
#include "gamepad.h"

class GamepadInputManager
{
public:
    GamepadInputManager();

    static GamepadInputManager &sharedInstance();

    void poll();

    bool checkQuit();

    GamepadSource &inputForPlayer(int playerNumber);

    void initialise();

private:
    std::unique_ptr<GamepadSource> gamepad;
};
