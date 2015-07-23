
#include "gfx/gfx.h"
#include "gametime.h"

#include "input/gamepadinputmanager.h"
#include "screenmanager.h"

#ifndef __WII__

#include <SDL/SDL.h>
#include "gfx/sdlfont.h"

#endif

int main(int argc, char **argv)
{
    const Font &boldFont = SDLFont("boldfont.ttf",16);
    const Font &regularFont = SDLFont("regularfont.ttf", 16);
    ResourceManager resourceManager(boldFont, regularFont);
    GfxWrapper gfxWrapper(640, 480, resourceManager);
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
