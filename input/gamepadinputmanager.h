#ifndef __GAMEPAD_INPUTMANAGER_H__
#define __GAMEPAD_INPUTMANAGER_H__

class Gamepad;

class GamepadInputManager
{
public:
	~GamepadInputManager();
	static GamepadInputManager *sharedInstance();
	void poll();

	Gamepad *playerOne();
	Gamepad *playerTwo();
	Gamepad *playerThree();
	Gamepad *playerFour();
private:
	GamepadInputManager();

	Gamepad *gamepadOne;
	Gamepad *gamepadTwo;
	Gamepad *gamepadThree;
	Gamepad *gamepadFour;

	static GamepadInputManager *instance;

};

#endif