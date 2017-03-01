
#include <gfx/gfx.h>
#include <gametime.h>

#include "gfx/sfmlgfx.h"

#include "input/gamepadinputmanager.h"
#include "screenmanager.h"

int main(int, char **)
{
    sf::RenderWindow window(sf::VideoMode(1280, 960), "Masteroids", sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    
    GameTime::setTimeProvider([](){
        static sf::Clock clockTime;
        return clockTime.getElapsedTime().asMilliseconds();
    });

    SFMLGfx gfxWrapper(window);
    
    ScreenManager screenManager;
    bool shouldRun = true;
	
    sf::Event event;
    while(shouldRun && window.isOpen())
	{
        gfxWrapper.waitForVBlank();
        gfxWrapper.fillScreen(RGB::BLACK);

        GamepadInputManager::sharedInstance().poll();
        
        shouldRun = screenManager.update(gfxWrapper);
        gfxWrapper.render();

		GameTime::tick();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
	}

	return 0;
}
