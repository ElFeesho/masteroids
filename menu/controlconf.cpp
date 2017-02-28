#include "controlconf.h"
#include "input/gamepadinputmanager.h"
#include "gametime.h"

ControlConf::ControlConf(ControlConfListener *nlistener)
		: listener(nlistener),
		  controlConfRenderer(ControlConfRenderer()),
		  menu_sel(0),
		  binding(-1),
		  bind_timeout(0),
		  next_change(GameTime::getMillis() + 500),
		  ldir(1)
{

}

void ControlConf::render(Gfx &gfx)
{
	renderer().render(gfx, position(), shape(), direction());
}

void ControlConf::menuScreenPresented() {

}

void ControlConf::menuScreenHidden() {

}

Position &ControlConf::position() {
	return Position::NONE;
}

Shape &ControlConf::shape() {
	return Shape::NONE;
}

Direction &ControlConf::direction() {
	return Direction::NONE;
}

AliveMonitor &ControlConf::aliveMonitor() {
	return alwaysAliveMonitor;
}

Renderer &ControlConf::renderer() {
	return controlConfRenderer;
}

bool ControlConf::update() {
	return true;
}