#ifndef __GAMEPAD_INPUTMANAGER_H__
#define __GAMEPAD_INPUTMANAGER_H__

class Gamepad;

class GamepadInputManager
{
public:
	~GamepadInputManager();

	static GamepadInputManager *sharedInstance();

	void poll();

	bool checkQuit();

	Gamepad *inputForPlayer(int playerNumber);

	void initialise();

private:
	GamepadInputManager();

	Gamepad *gamepads[4];

	static GamepadInputManager *instance;

};

#endif