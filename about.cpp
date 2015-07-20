#include "about.h"

#include "input/gamepadinputmanager.h"

static std::function<void()> aboutFinishHandler;

About::About(AboutListener *listener) : aboutRenderer(AboutRenderer()), listener(listener)
{
	aboutFinishHandler = [this](){
		this->listener->aboutClosed();
	};
    GamepadInputManager::sharedInstance().inputForPlayer(0).fire().addUpHandler(&aboutFinishHandler);
}

About::~About()
{
    GamepadInputManager::sharedInstance().inputForPlayer(0).fire().removeUpHandler(&aboutFinishHandler);
}

void About::render(GfxWrapper &gfx)
{
	renderer().render(gfx, position(), shape(), direction());
}

