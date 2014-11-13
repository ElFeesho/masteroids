#ifndef __GAMEPAD_H__
#define __GAMEPAD_H__

#include <vector>
#include <string>

using std::vector;

enum GamepadButton
{
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_FIRE,
	BUTTON_START
};

class GamepadSourceListener
{
public:
	virtual void buttonDown(GamepadButton button) = 0;
	virtual void buttonUp(GamepadButton button) = 0;
};

class GamepadSource
{
public:
	virtual ~GamepadSource() {}
	virtual void setListener(GamepadSourceListener *listener) = 0;
	virtual void poll() = 0;
	virtual const std::string name() const = 0;
};

class GamepadListener
{
public:
	GamepadListener() {};
	virtual ~GamepadListener() {};
	virtual void buttonDown(GamepadButton button) {};
	virtual void buttonUp(GamepadButton button) {};
};

class Gamepad : public GamepadSourceListener
{
public:
	Gamepad(GamepadSource *source) : source(source)
	{
		source->setListener(this);
	}

	~Gamepad()
	{
		source->setListener(0);
	}

	void addListener(GamepadListener *listener)
	{
		listeners.push_back(listener);
	}

	void removeListener(GamepadListener *listener)
	{
		for(int i = 0; i < listeners.size(); i++)
		{
			if(listeners.at(i) == listener)
			{
				listeners.erase(listeners.begin()+i);
			}
		}
	}

	void buttonDown(GamepadButton button)
	{
		for(int i = 0; i < listeners.size(); i++)
		{
			listeners.at(i)->buttonDown(button);
		}
	}

	void buttonUp(GamepadButton button)
	{
		for(int i = 0; i < listeners.size(); i++)
		{
			listeners.at(i)->buttonUp(button);
		}
	}

	const std::string name() const
	{
		return source->name();
	}

	void poll()
	{
		source->poll();
	}

private:
	vector<GamepadListener*> listeners;
	GamepadSource *source;
};

#endif
