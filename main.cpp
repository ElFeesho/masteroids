
#include "gfx/gfx.h"
#include "gametime.h"

#include "input/gamepadinputmanager.h"
#include "screenmanager.h"

#ifndef __WII__

#include <SDL/SDL.h>

#endif

int main(int argc, char **argv)
{
    GfxWrapper gfxWrapper(640, 480, ResourceManager());
	printf("Initialising graphics\n");

	printf("Initialised graphics\n");

    GamepadInputManager::sharedInstance().initialise();

	printf("Initialised input\n");

	ScreenManager screenManager = ScreenManager();
	for (; ;)
	{
        gfxWrapper.waitForVBlank();
        gfxWrapper.fillScreen(RGB::black);

        GamepadInputManager::sharedInstance().poll();
        screenManager.update(&gfxWrapper);
        gfxWrapper.render();
		GameTime::tick();

        if (GamepadInputManager::sharedInstance().checkQuit())
		{
			break;
		}
	}

	return 0;
}
