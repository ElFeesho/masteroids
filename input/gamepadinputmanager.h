#ifndef __GAMEPAD_INPUTMANAGER_H__
#define __GAMEPAD_INPUTMANAGER_H__

class Gamepad;

class GamepadInputManager {
public:
    ~GamepadInputManager();

    static GamepadInputManager *sharedInstance();

    void poll();

    Gamepad *inputForPlayer(int playerNumber);

private:
    GamepadInputManager();

    Gamepad *gamepads[4];

    static GamepadInputManager *instance;

};

#endif