#ifndef __KEYBOARDSOURCE_H__
#define __KEYBOARDSOURCE_H__

#include "gamepad.h"

class KeyboardSource : public GamepadSource {
public:
    KeyboardSource() {}
    ~KeyboardSource() {}

    void setListener(GamepadSourceListener *listener) {
        this->listener = listener;
    }

    void poll();

    const std::string name() const {
        return "Keyboard";
    }

private:
    GamepadSourceListener *listener { 0 };
    int keyState { 0 };
    int lastState { 0 };
};

#endif
