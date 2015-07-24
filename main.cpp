
#include "gfx/gfx.h"
#include "gametime.h"

#include "input/gamepadinputmanager.h"
#include "screenmanager.h"

#ifndef __WII__

#include "gfx/sfmlfont.h"

#endif

int main(int argc, char **argv)
{
    const Font &boldFont = SFMLFont("boldfont.ttf",16);
    const Font &regularFont = SFMLFont("regularfont.ttf", 16);
    ResourceManager resourceManager(boldFont, regularFont);
    GfxWrapper gfxWrapper(resourceManager);
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
