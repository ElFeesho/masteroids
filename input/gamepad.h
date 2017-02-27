#pragma once

#include <algorithm>
#include <vector>
#include <string>
#include <functional>

using std::vector;

class ButtonCommand
{
public:
    virtual ~ButtonCommand() {};
    virtual void buttonAction() = 0;
};

class ButtonCommandLambda : public ButtonCommand
{
public:
    ButtonCommandLambda(std::unique_ptr<std::function<void()>> &&handler);
    virtual void buttonAction() override;
private:
    std::unique_ptr<std::function<void()>> actionHandler;
};

class GamepadButton {
private:
    class EmptyCommand : public ButtonCommand
    {
    public:
        void buttonAction() override {}
    };
public:
    GamepadButton();

    void addDownHandler(ButtonCommand &downHandler);

    void addUpHandler(ButtonCommand &upHandler);

    void removeDownHandler();

    void removeUpHandler();

    void notifyDownHandlers();

    void notifyUpHandlers();

private:
    ButtonCommand *downHandler;
    ButtonCommand *upHandler;

    EmptyCommand empty;
};

class GamepadSource {
public:
    virtual ~GamepadSource() { }

    virtual void poll() = 0;

    virtual GamepadButton &fire() = 0;

    virtual GamepadButton &up() = 0;

    virtual GamepadButton &left() = 0;

    virtual GamepadButton &down() = 0;

    virtual GamepadButton &right() = 0;

    virtual GamepadButton &pause() = 0;

    virtual const std::string name() const = 0;
};
