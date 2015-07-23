#pragma once

#include "gamepad.h"

class GamepadInputManager
{
public:
    GamepadInputManager();
	~GamepadInputManager();

    static GamepadInputManager &sharedInstance();

    void poll();

    bool checkQuit();

    GamepadSource &inputForPlayer(int playerNumber);

    void initialise();

private:
    std::unique_ptr<GamepadSource> gamepad;
};
