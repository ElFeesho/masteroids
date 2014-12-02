#ifndef __DIRECTIONCONTROLLER_H__
#define __DIRECTIONCONTROLLER_H__

#include "input/gamepad.h"
#include "direction.h"

class DirectionController : public GamepadListener
{
public:
    DirectionController() : directionToControl(Direction::NONE) {}
    DirectionController(DirectionController &copy) : directionToControl(copy.directionToControl) {}
    DirectionController(Direction &directon) : directionToControl(directon) {}
    ~DirectionController() {}

    bool buttonDown(GamepadButton button) override {
        if(button == BUTTON_LEFT) {
            directionToControl.Spin(-0.1f);
        }
        else if(button == BUTTON_RIGHT)
        {
            directionToControl.Spin(0.1f);
        }
        else if(button == BUTTON_UP)
        {
            directionToControl.Speed(0.1f);
        }
        return true;
    }

    bool buttonUp(GamepadButton button) override {
        if(button == BUTTON_LEFT || button == BUTTON_RIGHT)
        {
            directionToControl.Spin(0.0f);
        }
        else if(button == BUTTON_UP)
        {
            directionToControl.Speed(0.0f);
        }
        return true;
    }

private:
    Direction &directionToControl;
};

#endif
