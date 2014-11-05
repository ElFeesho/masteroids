#ifndef __KEYBOARDSOURCE_H__
#define __KEYBOARDSOURCE_H__

#include "gamepad.h"

class KeyboardSource : public GamepadSource
{
public:
	KeyboardSource() : listener(0), keyState(0), lastState(0) {}

	~KeyboardSource() {}

	void setListener(GamepadSourceListener *listener)
	{
		this->listener = listener;
	}

	void poll();

	char *name()
	{
		return "Keyboard";
	}

private:
	GamepadSourceListener *listener;
	int keyState;
	int lastState;
};

#endif
