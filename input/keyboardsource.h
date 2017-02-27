#ifndef __WII__
#ifndef __KEYBOARDSOURCE_H__
#define __KEYBOARDSOURCE_H__

#include "gamepad.h"

class KeyboardSource : public GamepadSource
{
public:
    KeyboardSource();
    KeyboardSource(KeyboardSource &) = delete;
    KeyboardSource(KeyboardSource &&) = delete;
    ~KeyboardSource();

	void poll() override;

	const std::string name() const override
	{
		return "Keyboard";
	}

private:
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
