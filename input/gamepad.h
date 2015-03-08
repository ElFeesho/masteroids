#ifndef __GAMEPAD_H__
#define __GAMEPAD_H__

#include <algorithm>
#include <vector>
#include <string>
#include <functional>

using std::vector;

class GamepadButton
{
public:
	GamepadButton()
	{
	}

	~GamepadButton()
	{
	}

	void addDownHandler(std::function<void()> *handler)
	{
		downHandlers.push_back(handler);
	}

	void addUpHandler(std::function<void()> *handler)
	{
		upHandlers.push_back(handler);
	}

	void removeDownHandler(std::function<void()> *handler)
	{
		downHandlers.erase(std::find(downHandlers.begin(), downHandlers.end(), handler));
	}

	void removeUpHandler(std::function<void()> *handler)
	{
		upHandlers.erase(std::find(upHandlers.begin(), upHandlers.end(), handler));
	}

	void notifyDownHandlers()
	{
		for (auto handler : downHandlers)
		{
			(*handler)();
		}
	}

	void notifyUpHandlers()
	{
		for (auto handler : upHandlers)
		{
			(*handler)();
		}
	}

private:
	vector<std::function<void()>*> downHandlers;
	vector<std::function<void()>*> upHandlers;
};

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


#endif
