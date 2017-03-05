
#include <gfx/gfx.h>
#include <gametime.h>

#include "gfx/sfmlgfx.h"

#include "input/gamepadinputmanager.h"
#include "screenmanager.h"

int main(int, char **)
{
    
    GameTime::setTimeProvider([](){
        static sf::Clock clockTime;
        return clockTime.getElapsedTime().asMilliseconds();
    });

    SFMLGfx gfxWrapper;
    
    ScreenManager screenManager;
    bool shouldRun = true;
    
    while(shouldRun)
	{
        gfxWrapper.waitForVBlank();
        gfxWrapper.fillScreen(RGB::BLACK);

        GamepadInputManager::sharedInstance().poll();
        
        shouldRun = screenManager.update(gfxWrapper);
        gfxWrapper.render();

		GameTime::tick();
	}

	return 0;
}
