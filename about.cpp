#include "about.h"

#include "input/gamepadinputmanager.h"

static std::function<void()> aboutFinishHandler;

About::About(AboutListener *listener) : aboutRenderer(AboutRenderer()), listener(listener)
{
	aboutFinishHandler = [this](){
		this->listener->aboutClosed();
	};

}

About::~About()
{

}

void About::render(GfxWrapper &gfx)
{
	renderer().render(gfx, position(), shape(), direction());
}


void About::menuScreenPresented() {
    GamepadInputManager::sharedInstance().inputForPlayer(0).fire().addUpHandler(&aboutFinishHandler);
    GamepadInputManager::sharedInstance().inputForPlayer(0).pause().addUpHandler(&aboutFinishHandler);
}

void About::menuScreenHidden() {
    GamepadInputManager::sharedInstance().inputForPlayer(0).fire().removeUpHandler(&aboutFinishHandler);
    GamepadInputManager::sharedInstance().inputForPlayer(0).pause().removeUpHandler(&aboutFinishHandler);
}
