#include <iostream>
#include "about.h"

#include "input/gamepadinputmanager.h"

static std::function<void()> aboutFinishHandler;

About::About(AboutListener *nlistener) : listener(nlistener), aboutRenderer(AboutRenderer())
{
    std::cout << "About" << std::endl;
    aboutFinishHandler = [this](){
		this->listener->aboutClosed();
	};

}

About::~About()
{
    std::cout << "~About" << std::endl;
}

void About::render(Gfx &gfx)
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
