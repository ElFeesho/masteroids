#include <iostream>
#include "gamepad.h"

void GamepadButton::addDownHandler(std::function<void ()> *handler)
{
    downHandlers.push_back(handler);
}

void GamepadButton::addUpHandler(std::function<void ()> *handler)
{
    upHandlers.push_back(handler);
}

void GamepadButton::removeDownHandler(std::function<void ()> *handler)
{
    downHandlers.erase(std::find(downHandlers.begin(), downHandlers.end(), handler));
}

void GamepadButton::removeUpHandler(std::function<void ()> *handler)
{
    upHandlers.erase(std::find(upHandlers.begin(), upHandlers.end(), handler));
}

void GamepadButton::removeAllHandlers() {
    upHandlers.erase(upHandlers.begin(), upHandlers.end());
    downHandlers.erase(downHandlers.begin(), downHandlers.end());
}

void GamepadButton::notifyDownHandlers()
{
    for (auto handler : downHandlers)
    {
        (*handler)();
    }
}

void GamepadButton::notifyUpHandlers()
{
    for (auto handler : upHandlers)
    {
        (*handler)();
    }
}
