
#include "gfx/gfx.h"
#include "gametime.h"

#include "input/gamepadinputmanager.h"
#include "screenmanager.h"

#ifndef __WII__

#include "gfx/sfmlgfx.h"

#endif

int main(int, char **)
{
    sf::RenderWindow window(sf::VideoMode(1280, 960), "Masteroids", sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    SFMLGfx gfxWrapper(window);
    GamepadInputManager::sharedInstance().initialise();
    ScreenManager screenManager;
    bool shouldRun = true;
	while(shouldRun && window.isOpen())
	{
        gfxWrapper.waitForVBlank();
        gfxWrapper.fillScreen(RGB::BLACK);

        GamepadInputManager::sharedInstance().poll();
        shouldRun = screenManager.update(gfxWrapper);
        gfxWrapper.render();
		GameTime::tick();

        if (GamepadInputManager::sharedInstance().checkQuit())
		{
			break;
		}

        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
	}

	return 0;
}
