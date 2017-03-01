#include <iostream>
#include "about.h"

#include "input/gamepadinputmanager.h"

static std::function<void()> aboutFinishHandler;

About::About(AboutListener *nlistener)
{
    aboutFinishHandler = [nlistener](){
		nlistener->aboutClosed();
	};
}

bool About::update()
{
	return aliveMonitor().alive();
}

Position &About::position()
{
	return Position::NONE;
}

Shape &About::shape()
{
	return Shape::NONE;
}

Direction &About::direction()
{
	return Direction::NONE;
}

AliveMonitor &About::aliveMonitor()
{
    return alivemonitor;
}

Renderer &About::renderer()
{
	return aboutRenderer;
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
