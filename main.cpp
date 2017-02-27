#include "gfx/gfx.h"
#include "gametime.h"

#include "input/gamepadinputmanager.h"
#include "screenmanager.h"

#ifndef __WII__

#include "gfx/sfmlgfx.h"

#endif

int main(int, char **) {
    SFMLGfx gfxWrapper;
    GamepadInputManager::sharedInstance().initialise();
    ScreenManager screenManager;

    for (;;) {
        gfxWrapper.waitForVBlank();
        gfxWrapper.fillScreen(RGB::BLACK);

        GamepadInputManager::sharedInstance().poll();
        if (!screenManager.update(gfxWrapper))
        {
            break;
        }
        gfxWrapper.render();
        GameTime::tick();
        if (GamepadInputManager::sharedInstance().checkQuit() && gfxWrapper.checkQuit()) {
            break;
        }
    }

    return 0;
}
