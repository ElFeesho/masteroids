#include <input/gamepad.h>
#include "direction.h"

#ifndef __INPUTDIRECTIONCONTROLLER_H__
#define __INPUTDIRECTIONCONTROLLER_H__

class InputDirectionController : public GamepadListener
{
public:
    InputDirectionController() : gamepad(nullptr), direction(Direction()) {}

    InputDirectionController(Gamepad *gamepad, Direction &direction) : gamepad(gamepad), direction(direction)
    {
        gamepad->addListener(this);
    }

    ~InputDirectionController()
    {
        gamepad->removeListener(this);
    }

    bool buttonDown(GamepadButton button) override {
        if(button == BUTTON_LEFT)
        {
            direction.Spin(-0.5f);
        }
        else if(button == BUTTON_RIGHT)
        {
            direction.Spin(0.5f);
        }
        else if(button == BUTTON_UP)
        {
            direction.Speed(0.1f);
        }
        else
        {
            return false;
        }
        return true;
    }

    bool buttonUp(GamepadButton button) override {
        if(button == BUTTON_LEFT || button == BUTTON_RIGHT)
        {
            direction.Spin(0);
        }
        else if(button == BUTTON_UP)
        {
            direction.Speed(0.0f);
        }
        else
        {
            return false;
        }
        return true;
    }

private:
    Gamepad *gamepad;
    Direction &direction;

};

#endif