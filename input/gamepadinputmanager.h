#ifndef __GAMEPAD_INPUTMANAGER_H__
#define __GAMEPAD_INPUTMANAGER_H__

#include "gamepad.h"

class GamepadInputManager
{
public:
	~GamepadInputManager();

    static GamepadInputManager &sharedInstance();

    void poll();

    bool checkQuit();

    GamepadSource &inputForPlayer(int playerNumber);

    void initialise();

    GamepadInputManager();
private:

	GamepadSource *gamepads[4];

};

#endif
