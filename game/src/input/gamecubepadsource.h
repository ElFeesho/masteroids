#ifdef __WII__

#ifndef __GAMECUBEPADSOURCE_H__
#define __GAMECUBEPADSOURCE_H__

#include "gamepad.h"

class GamecubePadSource : public GamepadSource
{
public:
	GamecubePadSource(int padNumber)
	{
		this->padNumber = padNumber;
	}

	~GamecubePadSource()
	{
	}

	void poll();

	const std::string name() const
	{
		return "Gamecube Pad";
	}

private:
	int padNumber;
	int keyState{0};
	int lastState{0};
	GamepadButton fireButton { GamepadButton() };
	GamepadButton upButton { GamepadButton() };
	GamepadButton leftButton { GamepadButton() };
	GamepadButton rightButton { GamepadButton() };
	GamepadButton downButton { GamepadButton() };
	GamepadButton pauseButton { GamepadButton() };
public:
	virtual GamepadButton &fire() override;

	virtual GamepadButton &up() override;

	virtual GamepadButton &left() override;

	virtual GamepadButton &down() override;

	virtual GamepadButton &right() override;

	virtual GamepadButton &pause() override;
};

#endif

#endif
