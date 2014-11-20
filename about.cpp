#include "about.h"

#include "input/gamepadinputmanager.h"

About::About(AboutListener *listener) : aboutRenderer(AboutRenderer()), listener(listener) {
    GamepadInputManager::sharedInstance()->inputForPlayer(0)->addListener(this);
}

About::~About() {
    GamepadInputManager::sharedInstance()->inputForPlayer(0)->removeListener(this);
}

void About::render(GfxWrapper *gfx) {
    renderer().render(gfx, position(), shape(), direction());
}

bool About::buttonDown(GamepadButton button) {
    return false;
}

bool About::buttonUp(GamepadButton button) {
    if (button == BUTTON_FIRE || button == BUTTON_START) {
        listener->aboutClosed();
        return true;
    }
    return false;
}
