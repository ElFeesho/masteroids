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
    GamepadInputManager::sharedInstance().inputForPlayer(0).fire().addUpHandler(aboutFinishHandler);
    GamepadInputManager::sharedInstance().inputForPlayer(0).pause().addUpHandler(aboutFinishHandler);
}

void About::menuScreenHidden() {
    GamepadInputManager::sharedInstance().inputForPlayer(0).fire().removeUpHandler();
    GamepadInputManager::sharedInstance().inputForPlayer(0).pause().removeUpHandler();
}

bool About::update() {
    return aliveMonitor().alive();
}

Position &About::position() {
    return Position::NONE;
}

Shape &About::shape() {
    return Shape::NONE;
}

Direction &About::direction() {
    return Direction::NONE;
}

const AliveMonitor &About::aliveMonitor() {
    return alivemonitor;
}

const Renderer &About::renderer() {
    return aboutRenderer;
}