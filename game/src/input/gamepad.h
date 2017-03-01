#pragma once

#include <algorithm>
#include <vector>
#include <string>
#include <functional>

using std::vector;

class GamepadButton
{
public:
    void addDownHandler(std::function<void()> *handler);

    void addUpHandler(std::function<void()> *handler);

    void removeDownHandler(std::function<void()> *handler);

    void removeUpHandler(std::function<void()> *handler);

    void removeAllHandlers();

    void notifyDownHandlers();

    void notifyUpHandlers();

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
