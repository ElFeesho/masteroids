#ifndef __GAMEPAD_H__
#define __GAMEPAD_H__

#include <algorithm>
#include <vector>
#include <string>
#include <functional>

using std::vector;

class GamepadSource
{
public:
	virtual ~GamepadSource()
	{
	}

	virtual void poll() = 0;

	virtual GamepadButton &fire() = 0;
	virtual GamepadButton &up() = 0;
	virtual GamepadButton &left() = 0;
	virtual GamepadButton &down() = 0;
	virtual GamepadButton &right() = 0;
	virtual GamepadButton &pause() = 0;

	virtual const std::string name() const = 0;
};

class GamepadListener
{
public:
	GamepadListener()
	{
	};

	virtual ~GamepadListener()
	{
	};

	virtual bool buttonDown(GamepadButton button) = 0;

	virtual bool buttonUp(GamepadButton button) = 0;
};

class GamepadButton
{
public:
	GamepadButton(){}
	~GamepadButton(){}

	void addDownHandler(std::function &handler)
	{
		downHandlers.push_back(handler);
	}

	void addUpHandler(std::function &handler)
	{
		upHandlers.push_back(handler);
	}

	void removeDownHandler(std::function &handler)
	{
		downHandlers.erase(std::find(downHandlers.begin(), downHandlers.end(), handler));
	}

	void removeUpHandler(std::function &handler)
	{
		upHandlers.erase(std::find(upHandlers.begin(), upHandlers.end(), handler));
	}

	void notifyDownHandlers()
	{
		for(auto handler : downHandlers)
		{
			handler();
		}
	}

	void notifyUpHandlers()
	{
		for(auto handler : upHandlers)
		{
			handler();
		}
	}

private:
	vector<std::function&> downHandlers;
	vector<std::function&> upHandlers;
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
		listeners.erase(std::remove_if(listeners.begin(), listeners.end(), [&](GamepadListener *value)
		{
			return value == listener;
		}));
	}

	void buttonDown(GamepadButton button)
	{
		for (auto listener : listeners)
		{
			if (listener->buttonDown(button))
			{
				break;
			}
		}
	}

	void buttonUp(GamepadButton button)
	{
		for (auto listener : listeners)
		{
			if (listener->buttonUp(button))
			{
				break;
			}
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
	vector<GamepadListener *> listeners;
	GamepadSource *source;
};

#endif
