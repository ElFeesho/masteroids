
#include "gfx/gfx.h"
#include "gametime.h"

#include "input/gamepadinputmanager.h"
#include "screenmanager.h"

#ifndef __WII__

#include "gfx/sfmlgfx.h"
#include "gfx/sfmlfont.h"

#endif

int main(int argc, char **argv)
{

    SFMLGfx gfxWrapper;
    GamepadInputManager::sharedInstance().initialise();
    ScreenManager screenManager;
	for (; ;)
	{
        gfxWrapper.waitForVBlank();
        gfxWrapper.fillScreen(RGB::black);

        GamepadInputManager::sharedInstance().poll();
        screenManager.update(gfxWrapper);
        gfxWrapper.render();
		GameTime::tick();

        if (GamepadInputManager::sharedInstance().checkQuit())
		{
			break;
		}
	}

	return 0;
}
