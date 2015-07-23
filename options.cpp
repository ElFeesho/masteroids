#include "options.h"
#include "input/gamepadinputmanager.h"
#include "gametime.h"

Options::Options(OptionsListener *listener)
        : listener(listener),
          optionsRenderer(OptionsRenderer()),
          alive(true),
		  menu_sel(0),
		  next_change(GameTime::getMillis() + 500),
		  ldir(1),
          child(nullptr),
		  colour(RGB(1.0f, 1.0f, 1.0f)),
		  colourHighlight(RGB(1.0f, 0.8f, 0.0f))
{

}

Options::~Options()
{

}


void Options::menuScreenPresented() {
    GamepadSource &gamepadSource = GamepadInputManager::sharedInstance().inputForPlayer(0);
    gamepadSource.up().addDownHandler(&upPressedHandler);
    gamepadSource.left().addDownHandler(&leftPressedHandler);
    gamepadSource.right().addDownHandler(&rightPressedHandler);
    gamepadSource.down().addDownHandler(&downPressedHandler);
    gamepadSource.fire().addDownHandler(&firePressed);
    gamepadSource.pause().addDownHandler(&pausePressed);


    gamepadSource.up().addUpHandler(&buttonReleased);
    gamepadSource.left().addUpHandler(&buttonReleased);
    gamepadSource.right().addUpHandler(&buttonReleased);
    gamepadSource.down().addUpHandler(&buttonReleased);
}

void Options::menuScreenHidden() {
    GamepadSource &gamepadSource = GamepadInputManager::sharedInstance().inputForPlayer(0);
    gamepadSource.up().removeDownHandler(&upPressedHandler);
    gamepadSource.down().removeDownHandler(&downPressedHandler);
    gamepadSource.left().removeDownHandler(&leftPressedHandler);
    gamepadSource.right().removeDownHandler(&rightPressedHandler);
    gamepadSource.fire().removeDownHandler(&firePressed);
    gamepadSource.pause().removeDownHandler(&pausePressed);


    gamepadSource.up().removeUpHandler(&buttonReleased);
    gamepadSource.left().removeUpHandler(&buttonReleased);
    gamepadSource.right().removeUpHandler(&buttonReleased);
    gamepadSource.down().removeUpHandler(&buttonReleased);
}

bool Options::update()
{
    if (child != nullptr)
	{
        if (!child->update())
		{
			delete child;
			child = NULL;
		}
		return true;
	}

	return alive;
}

void Options::render(GfxWrapper &gfx)
{
	renderer().render(gfx, position(), shape(), direction());
}



int Options::lives = 3;
int Options::difficulty = 1;
bool Options::team_kill = false;
int Options::players = 1;
int Options::max_bullets = 5;
bool Options::music = false;
